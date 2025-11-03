#ifndef SERIALREADDATA_H
#define SERIALREADDATA_H

#include "./log/log.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


extern bool SaveCsv;           //保存数据标志

class SerialReadData : public QObject
{
    Q_OBJECT
public:
    explicit SerialReadData(QSerialPort *serial = nullptr,QObject *parent = nullptr);

    void SRDworking();    //线程任务函数
private:
    QSerialPort *m_pserial;
    QByteArray serialBuf;  //储存接收到的数据
    QMutex bufMutex;
    QFile CsvFile;         //Csv文件对象
    QString dtStr;         //Csv文件路径
signals:
    void sigDataSort(QByteArray serialBuf);
};

#endif // SERIALREADDATA_H
