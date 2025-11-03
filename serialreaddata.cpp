#include "serialreaddata.h"
#include <QMutexLocker>  // 新增

SerialReadData::SerialReadData(QSerialPort *serial,QObject *parent)
    : QObject{parent},CsvFile(QDir::currentPath() + QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + ".csv")
{
    Q_UNUSED(parent);
    qDebug() << "构造serial" <<serial;
    m_pserial = serial;
    qDebug() << "串口复制" << m_pserial;

    //打开CsvFile
    if(!CsvFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "open file fail";
    }else{
        qDebug() << "File created at: " << CsvFile.fileName();
    }
}

bool SaveCsv = false;           //保存数据标志
const int FRAME_LENGTH = 138;   // 固定帧长
const int FRAME_HEADER_LEN = 4; // 帧头"@DUP"长度
const char FRAME_HEADER[4] = {'@', 'D', 'U', 'P'}; // 帧头
const char FRAME_TAIL = '$';                       // 帧尾
const int MAX_BUFFER_SIZE = 4096;                  // 最大缓存限制（防止溢出）

void SerialReadData::SRDworking()
{
    // 1) 读取一次性可用数据并追加到缓存（在本线程内安全执行）
    QByteArray newData = m_pserial->readAll();
    if (!newData.isEmpty()) {
        QMutexLocker locker(&bufMutex);
        serialBuf += newData;
        qDebug() << "累积数据后缓存大小:" << serialBuf.size();
        // locker 会在作用域结束时释放，但我们需要在循环中局部使用 locker
    }

    // 2) 解析循环：保护对 serialBuf 的访问
    while (true) {
        QByteArray candidateFrame;
        {
            QMutexLocker locker(&bufMutex);

            if (serialBuf.size() < FRAME_LENGTH) {
                qDebug() << "缓存大小" << serialBuf.size() << "<" << FRAME_LENGTH << "，继续累积数据";
                break;
            }

            // 查找帧头
            int headerPos = -1;
            for (int i = 0; i <= serialBuf.size() - FRAME_HEADER_LEN; ++i) {
                if (serialBuf[i] == FRAME_HEADER[0] &&
                    serialBuf[i + 1] == FRAME_HEADER[1] &&
                    serialBuf[i + 2] == FRAME_HEADER[2] &&
                    serialBuf[i + 3] == FRAME_HEADER[3]) {
                    headerPos = i;
                    break;
                }
            }

            if (headerPos == -1) {
                // 保留可能的截断帧头
                if (serialBuf.size() > FRAME_HEADER_LEN - 1)
                    serialBuf = serialBuf.right(FRAME_HEADER_LEN - 1);
                break;
            }

            // 如果从帧头到末尾不足一帧，保留并等待
            if (serialBuf.size() - headerPos < FRAME_LENGTH) {
                serialBuf = serialBuf.mid(headerPos);
                qDebug() << "等待数据补全，当前缓存大小:" << serialBuf.size();
                break;
            }

            // 提取候选帧并验证帧尾
            candidateFrame = serialBuf.mid(headerPos, FRAME_LENGTH);
            if (candidateFrame[FRAME_LENGTH - 1] != FRAME_TAIL) {
                // 帧尾错，丢弃帧头前的一个字节继续查找
                serialBuf.remove(0, headerPos + 1);
                qDebug() << "帧尾错误，丢弃无效数据，继续查找";
                continue;
            }

            // 到这里 candidateFrame 是有效帧，先从缓存中移除它
            serialBuf.remove(0, headerPos + FRAME_LENGTH);
        } // 释放 bufMutex，下面可以安全 emit/写文件（避免槽重入死锁）

        // 3) 处理有效帧（写 CSV / 发信号）
        if (!candidateFrame.isEmpty()) {
            qDebug() << "解析到有效帧，长度:" << candidateFrame.size();
            // 发信号给分析线程（跨线程复制数据安全）
            emit sigDataSort(candidateFrame);

            // 写入 CSV（只写已解析的完整帧）
            if (SaveCsv && CsvFile.isOpen()) {
                QTextStream out(&CsvFile);
                for (int i = 0; i < candidateFrame.size(); ++i) {
                    QString hexString = QString::number(static_cast<unsigned char>(candidateFrame[i]), 16).toUpper();
                    if (hexString.size() == 1) hexString.prepend('0');
                    out << hexString;
                    if (i != candidateFrame.size() - 1) out << ",";
                }
                out << "\n";
                out.flush();
            }

        }
        // 循环继续尝试解析下一个完整帧
    } // while
    // 4) 缓存超限保护（在最后检查并修剪）
    {
        QMutexLocker locker(&bufMutex);
        if (serialBuf.size() > MAX_BUFFER_SIZE) {
            qWarning() << "缓存超过最大限制" << MAX_BUFFER_SIZE << "，保留可能的有效数据";
            serialBuf = serialBuf.right(FRAME_LENGTH - 1);
        }
    }
}
