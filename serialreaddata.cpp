#include "serialreaddata.h"

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

bool SaveCsv = true;           //保存数据标志

void SerialReadData::SRDworking()
{
    // while(m_pserial->waitForReadyRead(100)) {        //最长等待50ms
    //     serialBuf += m_pserial->readAll();
    // }

    serialBuf = m_pserial->readAll();
    qDebug() << "Bytes available before read:" << m_pserial->bytesAvailable();
    qDebug() << "Received data size:" << serialBuf.size();
    qDebug() << "Received data:" << serialBuf;
    qDebug() << "Recv hex:" << serialBuf.toHex(' ');

    //LOG_INFO((char *)"串口收到数据%s",serialBuf.toStdString());

    //发射信号给数据分拣线程
    emit sigDataSort(serialBuf);
    //qDebug() << serialBuf.toHex();

    if(SaveCsv == false)        //不需要保存则关闭文件
        CsvFile.close();

    // 确保 CsvFile 已经打开
    if(CsvFile.isOpen() && serialBuf.size() != 0 && SaveCsv) {
        QTextStream out(&CsvFile);  //创建一个文本流，向保存文件中写入文本

        for(int i = 0; i < serialBuf.size(); ++i) {
            QString hexString = QString::number(static_cast<unsigned char>(serialBuf[i]), 16).toUpper();

            // 保证每个十六进制数为两位数，补零
            if(hexString.size() == 1) {
                hexString.prepend('0');
            }

            // 写入文件，每个数值之间用逗号分隔
            out << hexString;
            if(i != serialBuf.size() - 1) {
                out << ",";
            }
        }
        out << "\n";
    }

    serialBuf.clear();
}
