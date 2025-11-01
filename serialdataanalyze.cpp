#include "serialdataanalyze.h"

SerialDataAnalyze::SerialDataAnalyze(QObject *parent)
    : QObject{parent}
{
    Q_UNUSED(parent);
}

//数据分析线程任务函数
void SerialDataAnalyze::SDAworking(QByteArray serialBuf)
{
  qDebug() << "SerialDataAnalyze:";
  qDebug() << serialBuf.toHex();

  // 根据帧头解析数据，并发送对应信号，显示在界面上
  if (serialBuf[FRAMESTART_BASE] == '@' &&
      serialBuf[FRAMESTART_BASE + 1] == 'D' &&
      serialBuf[FRAMESTART_BASE + 2] == 'U' &&
      serialBuf[FRAMESTART_BASE + 3] == 'P' &&
      serialBuf[FRAMEEND_BASE] == '$' &&
      serialBuf.size() == FRAMEEND_BASE + 1) {
    qDebug() << "STM32数据";
    emit sigAngleDataAnalyze(serialBuf);
    emit sigDepthDataAnalyze(serialBuf);
    emit sigGPSDataAnalyze(serialBuf);
    emit sigThrusterDataAnalyze(serialBuf);
    emit sigFluxgateDataAnalyze(serialBuf);
    emit sigJY901SDataAnalyze(serialBuf);
  } else {
    // 如果帧头为ASCII中字符部分则是普通调试信息
    qDebug() << "Emitting sigLogDataDisplay with data:" << serialBuf;
    emit sigLogDataDisplay(serialBuf);
  }
}


