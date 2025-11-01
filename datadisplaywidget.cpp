#include "datadisplaywidget.h"

DataDisplayWidget::DataDisplayWidget(int radius, QWidget *parent) :
    QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    mainLayout -> setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);
    splitter_1 = new QSplitter(this);
    splitter_1 -> setContentsMargins(0, 0, 0, 0);
    mainLayout -> addWidget(splitter_1);

    this->setFocusPolicy(Qt::ClickFocus);

    //初始化模式选择界面
    ModeSelectPage(radius);

    //定时器延时10ms后，初始化数据显示界面
    QTimer *delay = new QTimer(this);
    connect(delay, &QTimer::timeout, this, [=](){
        Init();
        delay->deleteLater();   //超时后释放内存
    });
    delay->setSingleShot(true);
    delay->start(10);
}

//该构造函数不使用
DataDisplayWidget::DataDisplayWidget(QTextStream &ts, int radius, QWidget *parent) :
    QWidget(parent)
{
    Q_UNUSED(ts);
    Q_UNUSED(radius);
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);

    this->setFocusPolicy(Qt::ClickFocus);

}

//在数据显示界面的设置栏
void DataDisplayWidget::ModeSelectPage(int radius){
    /* create settings page */
    modeName = "测试模式";
    ctrDescrip = "运动控制";
    settings = new SlidePage(radius, "默认设置", this->parentWidget());
    QWidget *whiteSpace = new QWidget(this);
    whiteSpace->setFixedHeight(30);
    textInputItem *rename = new textInputItem("当前模式", this);
    rename->setValue(modeName);
    textInputItem *redesc = new textInputItem("当前控制", this);
    redesc->setValue(ctrDescrip);
    QWidget *whiteSpace_2 = new QWidget(this);
    whiteSpace_2->setFixedHeight(30);
    textButton *saveBtn = new textButton("Save to file", this);
//    connect(saveBtn, &textButton::clicked, this, [=](){
//        QString savePath = QFileDialog::getSaveFileName(this, tr("Save map"), " ", tr("Map file(*.map)"));
//        if(!savePath.isEmpty())
//            SaveToFile(savePath);
//    });
    settings->AddContent(saveBtn);
    settings->AddContent(whiteSpace_2);
    settings->AddContent(whiteSpace);
    settings->AddContent(redesc);
    settings->AddContent(rename);
    settings->show();
}

void DataDisplayWidget::Init(){

    InitLayout();               //初始化总体布局
    InitJY901SWidget();         //初始化JY901S窗口
    InitFluxgateWidget();       //初始化磁通门窗口
    InitPropulsionSysWidget();  //初始化动力系统窗口
    InitLogWidget();            //初始化串口log窗口
    InitInfoWidget();           //初始化信息窗口
}

void DataDisplayWidget::InitLayout()
{
    //layout
    //1为最大的布局器，2，3，4分别为垂直布局器，对应左中右
    splitter_1 = new QSplitter(this);
    splitter_1->setOrientation(Qt::Horizontal);
    splitter_2 = new QSplitter(splitter_1);
    splitter_2->setOrientation(Qt::Vertical);
    splitter_3 = new QSplitter(splitter_1);
    splitter_3->setOrientation(Qt::Vertical);
    splitter_4 = new QSplitter(splitter_1);
    splitter_4->setOrientation(Qt::Vertical);

    mainLayout->addWidget(splitter_1);
    splitter_1->addWidget(splitter_2);
    splitter_1->addWidget(splitter_3);
    splitter_1->addWidget(splitter_4);

    sizepolicy = QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);
    sizepolicy.setVerticalPolicy(QSizePolicy::Expanding);
    sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);

    splitter_1->setSizePolicy(sizepolicy);
    splitter_2->setSizePolicy(sizepolicy);
    splitter_3->setSizePolicy(sizepolicy);
    splitter_4->setSizePolicy(sizepolicy);

    splitter_1->setStretchFactor(0,2);
    splitter_1->setStretchFactor(1,7);
    splitter_1->setStretchFactor(2,2);

    splitter_2->setStretchFactor(0,1);
    splitter_2->setStretchFactor(1,1);

    splitter_3->setStretchFactor(0,5);
    splitter_3->setStretchFactor(1,1);

    splitter_4->setStretchFactor(0,1);
    splitter_4->setStretchFactor(1,2);

    titleFont = QFont("Corbel", 20);        //设定标题字体和大小
}

void DataDisplayWidget::InitJY901SWidget()
{
    //JY901S
    JY901STitle = new QLabel(this);
    JY901STitle->setText("JY901S");
    JY901STitle->setFont(titleFont);
    JY901STitle->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    JY901STitle->setStyleSheet("color:#2c2c2c");

    //小横条设置
    QWidget *JY901SSplitter = new QWidget(this);
    JY901SSplitter->setFixedSize(30, 6);
    JY901SSplitter->setStyleSheet("background-color:#3c3c3c;border-radius:3px;");

    QLabel *JY901SAcc = new QLabel("Acc:",this);    //JY901S加速度数据标签
    QLabel *JY901SGyro = new QLabel("Gyro:",this);   //JY901S中角速度标签
    QLabel *JY901SAngle = new QLabel("Angle:",this);  //JY901S中欧拉角标签
    QLabel *JY901SMag = new QLabel("Mag:",this);    //JY901S中磁场标签

    //设置字体和大小
    QFont JY901SDataFont = QFont("Corbel", 15);

    JY901SAcc->setMinimumHeight(25);
    JY901SAcc->setFont(JY901SDataFont);
    JY901SGyro->setMinimumHeight(25);
    JY901SGyro->setFont(JY901SDataFont);
    JY901SAngle->setMinimumHeight(25);
    JY901SAngle->setFont(JY901SDataFont);
    JY901SMag->setMinimumHeight(25);
    JY901SMag->setFont(JY901SDataFont);

    JY901SDataAcc->setMinimumSize(300,25);
    JY901SDataAcc->setFont(JY901SDataFont);
    JY901SDataGyro->setMinimumSize(300,25);
    JY901SDataGyro->setFont(JY901SDataFont);
    JY901SDataAngle->setMinimumSize(300,25);
    JY901SDataAngle->setFont(JY901SDataFont);
    JY901SDataMag->setMinimumSize(300,25);
    JY901SDataMag->setFont(JY901SDataFont);

    QWidget *JY901SDataWidget = new QWidget(this);
    JY901SDataWidget->setSizePolicy(sizepolicy);
    //设置最小大小
    JY901SDataWidget->setMinimumSize(300,250);
    QVBoxLayout *JY901SDataLayout = new QVBoxLayout(this);
    JY901SDataWidget->setLayout(JY901SDataLayout);
    JY901SDataLayout->setContentsMargins(0, 0, 0, 0);
    JY901SDataLayout->setAlignment(Qt::AlignTop);
    JY901SDataLayout->addWidget(JY901SAcc);
    JY901SDataLayout->addWidget(JY901SDataAcc);
    JY901SDataLayout->addWidget(JY901SGyro);
    JY901SDataLayout->addWidget(JY901SDataGyro);
    JY901SDataLayout->addWidget(JY901SAngle);
    JY901SDataLayout->addWidget(JY901SDataAngle);
    JY901SDataLayout->addWidget(JY901SMag);
    JY901SDataLayout->addWidget(JY901SDataMag);

    JY901SWidget = new QWidget(this);
    JY901SWidget->setSizePolicy(sizepolicy);
    QVBoxLayout *JY901SLayout = new QVBoxLayout(this);
    JY901SWidget->setLayout(JY901SLayout);
    JY901SLayout->setContentsMargins(0, 0, 0, 0);
    JY901SLayout->setAlignment(Qt::AlignTop);
    JY901SLayout->addWidget(JY901STitle);
    JY901SLayout->addWidget(JY901SSplitter);
    JY901SLayout->addWidget(JY901SDataWidget);

    splitter_2->addWidget(JY901SWidget);
    //splitter_2->addWidget(splitter_3);
}

void DataDisplayWidget::InitFluxgateWidget()
{
    //Fluxgate
    FluxgateTitle = new QLabel(this);
    FluxgateTitle->setText("Fluxgate");
    FluxgateTitle->setFont(titleFont);
    FluxgateTitle->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    FluxgateTitle->setStyleSheet("color:#2c2c2c");

    //小横条设置
    QWidget *FluxgateSplitter = new QWidget(this);
    FluxgateSplitter->setFixedSize(30, 6);
    FluxgateSplitter->setStyleSheet("background-color:#3c3c3c;border-radius:3px;");

    QLabel *FluxgateNO1 = new QLabel("NO1:",this);    //Fluxgate 1号标签
    QLabel *FluxgateNO2 = new QLabel("NO2:",this);    //Fluxgate 2号标签
    QLabel *FluxgateNO3 = new QLabel("NO3:",this);    //Fluxgate 3号标签
    QLabel *FluxgateNO4 = new QLabel("NO4:",this);    //Fluxgate 4号标签

    //设置字体和大小
    QFont FluxgateDataFont = QFont("Corbel", 15);

    FluxgateNO1->setMinimumHeight(25);
    FluxgateNO1->setFont(FluxgateDataFont);
    FluxgateNO2->setMinimumHeight(25);
    FluxgateNO2->setFont(FluxgateDataFont);
    FluxgateNO3->setMinimumHeight(25);
    FluxgateNO3->setFont(FluxgateDataFont);
    FluxgateNO4->setMinimumHeight(25);
    FluxgateNO4->setFont(FluxgateDataFont);

    FluxgateDataNO1->setMinimumSize(300,25);
    FluxgateDataNO1->setFont(FluxgateDataFont);
    FluxgateDataNO2->setMinimumSize(300,25);
    FluxgateDataNO2->setFont(FluxgateDataFont);
    FluxgateDataNO3->setMinimumSize(300,25);
    FluxgateDataNO3->setFont(FluxgateDataFont);
    FluxgateDataNO4->setMinimumSize(300,25);
    FluxgateDataNO4->setFont(FluxgateDataFont);

    QWidget *FluxgateDataWidget = new QWidget(this);
    FluxgateDataWidget->setSizePolicy(sizepolicy);
    FluxgateDataWidget->setMinimumSize(300,250);
    QVBoxLayout *FluxgateDataLayout = new QVBoxLayout(this);
    FluxgateDataWidget->setLayout(FluxgateDataLayout);
    FluxgateDataLayout->setContentsMargins(0, 0, 0, 0);
    FluxgateDataLayout->setAlignment(Qt::AlignTop);
    FluxgateDataLayout->addWidget(FluxgateNO1);
    FluxgateDataLayout->addWidget(FluxgateDataNO1);
    FluxgateDataLayout->addWidget(FluxgateNO2);
    FluxgateDataLayout->addWidget(FluxgateDataNO2);
    FluxgateDataLayout->addWidget(FluxgateNO3);
    FluxgateDataLayout->addWidget(FluxgateDataNO3);
    FluxgateDataLayout->addWidget(FluxgateNO4);
    FluxgateDataLayout->addWidget(FluxgateDataNO4);


    FluxgateWidget = new QWidget(this);
    FluxgateWidget->setSizePolicy(sizepolicy);
    QVBoxLayout *FluxgateLayout = new QVBoxLayout(this);
    FluxgateWidget->setLayout(FluxgateLayout);
    FluxgateLayout->setContentsMargins(0, 0, 0, 0);
    FluxgateLayout->setAlignment(Qt::AlignTop);
    FluxgateLayout->addWidget(FluxgateTitle);
    FluxgateLayout->addWidget(FluxgateSplitter);
    FluxgateLayout->addWidget(FluxgateDataWidget);

    splitter_2->addWidget(FluxgateWidget);
}

void DataDisplayWidget::InitPropulsionSysWidget()
{
    //动力系统
    QLabel *PropulsionSysLabel = new QLabel(this);
    PropulsionSysLabel->setText("Propulsion System");
    PropulsionSysLabel->setFont(titleFont);
    PropulsionSysLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    PropulsionSysLabel->setStyleSheet("color:#2c2c2c");

    //小横条设置
    QWidget *PropulsionSysSplitter = new QWidget(this);
    PropulsionSysSplitter->setFixedSize(30, 6);
    PropulsionSysSplitter->setStyleSheet("background-color:#3c3c3c;border-radius:3px;");

    //推进器名称标签和数据标签设置
    QLabel *Thruster1 = new QLabel("Thruster1",this);
    QLabel *Thruster2 = new QLabel("Thruster2",this);
    QLabel *Thruster3 = new QLabel("Thruster3",this);
    QLabel *Thruster4 = new QLabel("Thruster4",this);

    //设置字体和大小
    QFont ThrusterDataFont = QFont("Corbel", 15);

    Thruster1->setMinimumHeight(25);
    Thruster1->setFont(ThrusterDataFont);
    Thruster2->setMinimumHeight(25);
    Thruster2->setFont(ThrusterDataFont);
    Thruster3->setMinimumHeight(25);
    Thruster3->setFont(ThrusterDataFont);
    Thruster4->setMinimumHeight(25);
    Thruster4->setFont(ThrusterDataFont);

    ThrusterData1->setMinimumSize(100,20);
    ThrusterData1->setFont(ThrusterDataFont);
    ThrusterData2->setMinimumSize(100,20);
    ThrusterData2->setFont(ThrusterDataFont);
    ThrusterData3->setMinimumSize(100,20);
    ThrusterData3->setFont(ThrusterDataFont);
    ThrusterData4->setMinimumSize(100,20);
    ThrusterData4->setFont(ThrusterDataFont);

    //舵机名称标签和数据标签设置
    QLabel *Servo1 = new QLabel("Servo1",this);
    QLabel *Servo2 = new QLabel("Servo2",this);
    QLabel *Servo3 = new QLabel("Servo3",this);
    QLabel *Servo4 = new QLabel("Servo4",this);

    //设置字体和大小
    QFont ServoDataFont = QFont("Corbel", 15);

    Servo1->setMinimumHeight(25);
    Servo1->setFont(ServoDataFont);
    Servo2->setMinimumHeight(25);
    Servo2->setFont(ServoDataFont);
    Servo3->setMinimumHeight(25);
    Servo3->setFont(ServoDataFont);
    Servo4->setMinimumHeight(25);
    Servo4->setFont(ServoDataFont);

    ServoData1->setMinimumSize(100,20);
    ServoData1->setFont(ServoDataFont);
    ServoData2->setMinimumSize(100,20);
    ServoData2->setFont(ServoDataFont);
    ServoData3->setMinimumSize(100,20);
    ServoData3->setFont(ServoDataFont);
    ServoData4->setMinimumSize(100,20);
    ServoData4->setFont(ServoDataFont);

    //将推进器相关的控件垂直布局
    QWidget *ThrusterDataWidget = new QWidget(this);
    QVBoxLayout *ThrusterDataLayout = new QVBoxLayout(this);
    ThrusterDataWidget->setLayout(ThrusterDataLayout);
    ThrusterDataLayout->setContentsMargins(0, 0, 0, 0);
    ThrusterDataLayout->setAlignment(Qt::AlignTop);
    ThrusterDataLayout->addWidget(Thruster1);
    ThrusterDataLayout->addWidget(ThrusterData1);
    ThrusterDataLayout->addWidget(Thruster2);
    ThrusterDataLayout->addWidget(ThrusterData2);
    ThrusterDataLayout->addWidget(Thruster3);
    ThrusterDataLayout->addWidget(ThrusterData3);
    ThrusterDataLayout->addWidget(Thruster4);
    ThrusterDataLayout->addWidget(ThrusterData4);

    //将舵机相关的控件垂直布局
    QWidget *ServoDataWidget = new QWidget(this);
    QVBoxLayout *ServoDataLayout = new QVBoxLayout(this);
    ServoDataWidget->setLayout(ServoDataLayout);
    ServoDataLayout->setContentsMargins(0, 0, 0, 0);
    ServoDataLayout->setAlignment(Qt::AlignTop);
    ServoDataLayout->addWidget(Servo1);
    ServoDataLayout->addWidget(ServoData1);
    ServoDataLayout->addWidget(Servo2);
    ServoDataLayout->addWidget(ServoData2);
    ServoDataLayout->addWidget(Servo3);
    ServoDataLayout->addWidget(ServoData3);
    ServoDataLayout->addWidget(Servo4);
    ServoDataLayout->addWidget(ServoData4);

    //将推进器和舵机的布局再进行水平布局
    QWidget *PropulsionSysDataWidget = new QWidget(this);
    QHBoxLayout *PropulsionSysDataLayout = new QHBoxLayout(this);
    PropulsionSysDataWidget->setLayout(PropulsionSysDataLayout);
    PropulsionSysDataLayout->setContentsMargins(0, 0, 0, 0);
    PropulsionSysDataLayout->setAlignment(Qt::AlignTop);
    PropulsionSysDataLayout->addWidget(ThrusterDataWidget);
    PropulsionSysDataLayout->addWidget(ServoDataWidget);

    QWidget *PropulsionSysWidget = new QWidget(this);
    QVBoxLayout *PropulsionSysLayout = new QVBoxLayout(PropulsionSysWidget);
    PropulsionSysWidget->setLayout(PropulsionSysLayout);
    PropulsionSysLayout->setContentsMargins(0, 0, 0, 0);
    PropulsionSysLayout->setAlignment(Qt::AlignTop);
    PropulsionSysLayout->addWidget(PropulsionSysLabel);
    PropulsionSysLayout->addWidget(PropulsionSysSplitter);
    PropulsionSysLayout->addWidget(PropulsionSysDataWidget);

    splitter_3->addWidget(PropulsionSysWidget);
}

void DataDisplayWidget::InitLogWidget()
{
    //串口LOG
    //log标签设置
    QLabel *logLabel = new QLabel(this);
    logLabel->setText("Log From Uart");
    logLabel->setFont(titleFont);
    logLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    logLabel->setStyleSheet("color:#2c2c2c");

    //小横条设置
    QWidget *logSplitter = new QWidget(this);
    logSplitter->setFixedSize(30, 6);
    logSplitter->setStyleSheet("background-color:#3c3c3c;border-radius:3px;");

    //log框设置，包含PTE和LE，使用垂直布局
    //用于显示接收串口传过来的数据
    logPTE = new QPlainTextEdit;
    logPTE->setReadOnly(true);
    logPTE->setMinimumSize(300,185);
    logPTE->setStyleSheet("color: black; border-radius:3px; background-color: white; font: 20px 'Corbel Light'; border: 1px solid darkgray;");

    //串口发送行
    logTII = new textInputItem("Send Line:",this);

    QWidget *logWidget = new QWidget(this);
    QVBoxLayout *logLayout = new QVBoxLayout(this); //垂直布局
    logWidget->setLayout(logLayout);
    logWidget->setContentsMargins(0, 0, 0, 0);
    logLayout->setAlignment(Qt::AlignTop);
    logLayout->addWidget(logLabel);
    logLayout->addWidget(logSplitter);
    logLayout->addWidget(logPTE);
    logLayout->addWidget(logTII);

    //底下两个按钮的设置，使用水平布局
    textButton *SendBTN = new textButton("Send",this);
    textButton *ClearBTN = new textButton("Clear",this);

    //按下发送键，发送发送数据信号给主窗口
    connect(SendBTN,&textButton::clicked,this,[=](){
        emit sigLogDataSend();
    });

    //按下清屏键，清除接收框和发送框所有的数据
    connect(ClearBTN,&textButton::clicked,this,[=]()
    {
        logPTE->clear();
        logTII->setValue("");
        qDebug() << "Clear complete";
    });

    QWidget *BTNWidget = new QWidget(this);
    QHBoxLayout *BTNLayout = new QHBoxLayout(this); //水平布局
    BTNWidget->setLayout(BTNLayout);
    BTNLayout->addWidget(SendBTN);
    BTNLayout->addWidget(ClearBTN);

    //垂直布局，将logWidget、BTNWidget摆放
    splitter_3->addWidget(logWidget);
    splitter_3->addWidget(BTNWidget);
}

void DataDisplayWidget::InitInfoWidget()
{
    //info 显示深度、GPS、电量百分比
    infoTitle = new QLabel(this);
    infoTitle->setText("INFO");
    infoTitle->setFont(TitleFont);
    infoTitle->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    infoTitle->setStyleSheet("color:#2c2c2c");

    //info底下的小横条
    QWidget *infoSplitter = new QWidget(this);
    //info底下的小横条长度30，高度6
    infoSplitter->setFixedSize(30, 6);
    infoSplitter->setStyleSheet("background-color:#3c3c3c;border-radius:3px;");

    QFont InfoTitleFont = QFont("Corbel",18);
    QFont InfoDataFont = QFont("Arial",15);

    //姿态信息标题
    QLabel *AttitudeInfo = new QLabel(this);
    AttitudeInfo->setText("Angle:");
    AttitudeInfo->setMinimumHeight(25);
    AttitudeInfo->setFont(InfoTitleFont);

    AttitudeDataInfo->setMinimumHeight(25);
    AttitudeInfo->setFont(InfoDataFont);
    AttitudeDataInfo->setStyleSheet("background-color: black; color: black;border-radius:3px; background-color: #00000000; border: 1px solid darkgray;");

    //深度信息标题
    QLabel *DepthInfo = new QLabel(this);
    DepthInfo->setText("Depth:");
    DepthInfo->setMinimumHeight(25);
    DepthInfo->setFont(InfoTitleFont);

    DepthDataInfo->setMinimumHeight(25);
    DepthDataInfo->setFont(InfoDataFont);
    DepthDataInfo->setStyleSheet("background-color: black; color: black;border-radius:3px; background-color: #00000000; border: 1px solid darkgray;");

    //GPS信息
    QLabel *GPSInfo = new QLabel(this);
    GPSInfo->setText("GPS:");
    GPSInfo->setMinimumHeight(25);
    GPSInfo->setFont(InfoTitleFont);

    GPSDataInfo->setMinimumHeight(25);
    GPSDataInfo->setFont(InfoDataFont);
    GPSDataInfo->setStyleSheet("background-color: black; color: black;border-radius:3px; background-color: #00000000; border: 1px solid darkgray;");

    //手柄数据输出
    QLabel *JoystickInfo = new QLabel(this);
    JoystickInfo->setText("Joystick:");
    JoystickInfo->setMinimumHeight(25);
    JoystickInfo->setFont(InfoTitleFont);

    JoystickAxisDataInfo->setMinimumHeight(25);
    JoystickAxisDataInfo->setFont(InfoDataFont);
    JoystickAxisDataInfo->setStyleSheet("background-color: black; color: black;border-radius:3px; background-color: #00000000; border: 1px solid darkgray;");

    JoystickButtonDataInfo->setMinimumHeight(25);
    JoystickButtonDataInfo->setFont(InfoDataFont);
    JoystickButtonDataInfo->setStyleSheet("background-color: black; color: black;border-radius:3px; background-color: #00000000; border: 1px solid darkgray;");

    infoWidget = new QWidget(this);
    infoWidget->setSizePolicy(sizepolicy);
    QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);
    infoWidget->setMinimumSize(300,350);
    infoWidget->setLayout(infoLayout);
    infoLayout->setContentsMargins(10, 0, 0, 0);
    infoLayout->setAlignment(Qt::AlignTop);
    infoLayout->addWidget(infoTitle);
    infoLayout->addWidget(infoSplitter);
    infoLayout->addWidget(AttitudeInfo);
    infoLayout->addWidget(AttitudeDataInfo);
    infoLayout->addWidget(DepthInfo);
    infoLayout->addWidget(DepthDataInfo);
    infoLayout->addWidget(GPSInfo);
    infoLayout->addWidget(GPSDataInfo);
    infoLayout->addWidget(JoystickInfo);
    infoLayout->addWidget(JoystickAxisDataInfo);
    infoLayout->addWidget(JoystickButtonDataInfo);

    splitter_4->addWidget(infoWidget);
}

void DataDisplayWidget::slotLogDataDisplay(QByteArray serialBuf)
{
    if(!this->isHidden())
    {
        QTextCursor cursor = logPTE->textCursor();
        cursor.movePosition(QTextCursor::End);
        logPTE->setTextCursor(cursor);
        logPTE->insertPlainText(QString(serialBuf));
        logPTE->ensureCursorVisible();
        // qDebug() << "insertText data:" << serialBuf;
    }
}

void DataDisplayWidget::slotAngleDataDisplay(QByteArray ProcessedData)
{
    if(!this->isHidden())
    {
        float Roll,Pitch,Yaw;
        //拷贝数据
        std::memcpy(&Roll,&ProcessedData[ANGLE_BASE],FLOAT_SIZE);
        std::memcpy(&Pitch,&ProcessedData[ANGLE_BASE + FLOAT_SIZE],FLOAT_SIZE);
        std::memcpy(&Yaw,&ProcessedData[ANGLE_BASE + 2 * FLOAT_SIZE],FLOAT_SIZE);
        //显示在log里面
        AttitudeDataInfo->setText(QString("Roll%1  Pitch%2  Yaw%3")
                                      .arg(QString::number(Roll, 'f', 2)    // 横滚角，格式化为2位小数
                                          ,QString::number(Pitch, 'f', 2)   // 俯仰角，格式化为2位小数
                                          ,QString::number(Yaw, 'f', 2)));  // 偏航角，格式化为2位小数
        //显示在JY901S里面
        JY901SDataAngle->setText(QString("Roll%1  Pitch%2  Yaw%3")
                                      .arg(QString::number(Roll, 'f', 2)    // 横滚角，格式化为2位小数
                                          ,QString::number(Pitch, 'f', 2)   // 俯仰角，格式化为2位小数
                                          ,QString::number(Yaw, 'f', 2)));  // 偏航角，格式化为2位小数
    }
}

void DataDisplayWidget::slotFluxgateDataDisplay(QByteArray ProcessedData)
{
    if(!this->isHidden())
    {
        float FluxgateX1,FluxgateY1,FluxgateZ1;
        std::memcpy(&FluxgateX1,&ProcessedData[GRADIENTMAGNET_BASE                 ],FLOAT_SIZE);
        std::memcpy(&FluxgateY1,&ProcessedData[GRADIENTMAGNET_BASE +     FLOAT_SIZE],FLOAT_SIZE);
        std::memcpy(&FluxgateZ1,&ProcessedData[GRADIENTMAGNET_BASE + 2 * FLOAT_SIZE],FLOAT_SIZE);
        FluxgateDataNO1->setText(QString("X:%1 Y:%2 Z:%3").arg(QString::number(FluxgateX1 * 10000, 'f', 0)
                                                              ,QString::number(FluxgateX1 * 10000, 'f', 0)
                                                              ,QString::number(FluxgateX1 * 10000, 'f', 0)));

        float FluxgateX2,FluxgateY2,FluxgateZ2;
        std::memcpy(&FluxgateX2,&ProcessedData[GRADIENTMAGNET_BASE + 3 * FLOAT_SIZE],FLOAT_SIZE);
        std::memcpy(&FluxgateY2,&ProcessedData[GRADIENTMAGNET_BASE + 4 * FLOAT_SIZE],FLOAT_SIZE);
        std::memcpy(&FluxgateZ2,&ProcessedData[GRADIENTMAGNET_BASE + 5 * FLOAT_SIZE],FLOAT_SIZE);
        FluxgateDataNO2->setText(QString("X:%1 Y:%2 Z:%3").arg(QString::number(FluxgateX2 * 10000, 'f', 0)
                                                              ,QString::number(FluxgateY2 * 10000, 'f', 0)
                                                              ,QString::number(FluxgateZ2 * 10000, 'f', 0)));

        float FluxgateX3,FluxgateY3,FluxgateZ3;
        std::memcpy(&FluxgateX3,&ProcessedData[GRADIENTMAGNET_BASE + 6 * FLOAT_SIZE],FLOAT_SIZE);
        std::memcpy(&FluxgateY3,&ProcessedData[GRADIENTMAGNET_BASE + 7 * FLOAT_SIZE],FLOAT_SIZE);
        std::memcpy(&FluxgateZ3,&ProcessedData[GRADIENTMAGNET_BASE + 8 * FLOAT_SIZE],FLOAT_SIZE);
        FluxgateDataNO3->setText(QString("X:%1 Y:%2 Z:%3").arg(QString::number(FluxgateX3 * 10000, 'f', 0)
                                                              ,QString::number(FluxgateY3 * 10000, 'f', 0)
                                                              ,QString::number(FluxgateZ3 * 10000, 'f', 0)));
        float FluxgateX4,FluxgateY4,FluxgateZ4;
        std::memcpy(&FluxgateX4,&ProcessedData[GRADIENTMAGNET_BASE + 9 * FLOAT_SIZE],FLOAT_SIZE);
        std::memcpy(&FluxgateY4,&ProcessedData[GRADIENTMAGNET_BASE + 10 * FLOAT_SIZE],FLOAT_SIZE);
        std::memcpy(&FluxgateZ4,&ProcessedData[GRADIENTMAGNET_BASE + 11 * FLOAT_SIZE],FLOAT_SIZE);
        FluxgateDataNO4->setText(QString("X:%1 Y:%2 Z:%3").arg(QString::number(FluxgateX4 * 10000, 'f', 0)
                                                              ,QString::number(FluxgateY4 * 10000, 'f', 0)
                                                              ,QString::number(FluxgateZ4 * 10000, 'f', 0)));
    }
}

void DataDisplayWidget::slotThrusterDataDisplay(QByteArray ProcessedData)
{
    if(!this->isHidden())
    {
        unsigned short DataTemp;    //数据缓存

        std::memcpy(&DataTemp,&ProcessedData[THRUSTER_BASE],UINT16_T_SIZE);
        ThrusterData1->setText(QString("%1").arg(QString::number(DataTemp)));

        std::memcpy(&DataTemp,&ProcessedData[THRUSTER_BASE + UINT16_T_SIZE],UINT16_T_SIZE);
        ThrusterData2->setText(QString("%1").arg(QString::number(DataTemp)));

        std::memcpy(&DataTemp,&ProcessedData[THRUSTER_BASE + 2 * UINT16_T_SIZE],UINT16_T_SIZE);
        ThrusterData3->setText(QString("%1").arg(QString::number(DataTemp)));

        std::memcpy(&DataTemp,&ProcessedData[THRUSTER_BASE + 3 * UINT16_T_SIZE],UINT16_T_SIZE);
        ThrusterData4->setText(QString("%1").arg(QString::number(DataTemp)));

        std::memcpy(&DataTemp,&ProcessedData[SERVO_BASE],UINT16_T_SIZE);
        ServoData1->setText(QString("%1").arg(QString::number(DataTemp)));

        std::memcpy(&DataTemp,&ProcessedData[SERVO_BASE + UINT16_T_SIZE],UINT16_T_SIZE);
        ServoData2->setText(QString("%1").arg(QString::number(DataTemp)));

        std::memcpy(&DataTemp,&ProcessedData[SERVO_BASE + 2 * UINT16_T_SIZE],UINT16_T_SIZE);
        ServoData3->setText(QString("%1").arg(QString::number(DataTemp)));

        std::memcpy(&DataTemp,&ProcessedData[SERVO_BASE + 3 * UINT16_T_SIZE],UINT16_T_SIZE);
        ServoData4->setText(QString("%1").arg(QString::number(DataTemp)));
    }
}

void DataDisplayWidget::slotDepthDataDisplay(QByteArray ProcessedData)
{
    if(!this->isHidden())
    {
        float Depth;
        std::memcpy(&Depth,&ProcessedData[DEPTH_BASE],FLOAT_SIZE);
        DepthDataInfo->setText(QString("%1cm").arg(QString::number(Depth, 'f', 2)));     //深度cm
    }
}

void DataDisplayWidget::slotGPSDataDisplay(QByteArray ProcessedData)
{
    if(!this->isHidden())
    {
        float Latitude,Longitude;   //纬度和经度

        std::memcpy(&Longitude,&ProcessedData[GPS_BASE + UINT8_T_SIZE],FLOAT_SIZE);
        std::memcpy(&Latitude,&ProcessedData[GPS_BASE + 2 * UINT8_T_SIZE + FLOAT_SIZE],FLOAT_SIZE);

        GPSDataInfo->setText(QString("%1 %2 %3 %4 %5")    //有效性 东西 经值 南北 维值
                                 .arg(static_cast<char>(ProcessedData[GPS_BASE + 2 * UINT8_T_SIZE + 2 * FLOAT_SIZE]))  // 有效性
                                 .arg(static_cast<char>(ProcessedData[GPS_BASE]))  // 东西
                                 .arg(QString::number(Longitude, 'f', 5))  // 经度，格式化为6位小数
                                 .arg(static_cast<char>(ProcessedData[GPS_BASE + UINT8_T_SIZE + FLOAT_SIZE]))  // 南北
                                 .arg(QString::number(Latitude, 'f', 5)));  // 纬度，格式化为6位小数
    }
}

void DataDisplayWidget::slotJY901SDataDisplay(QByteArray ProcessedData)
{
  qDebug() << "Received JY901S data:" << ProcessedData.toHex();
  if (!this->isHidden()) {
    float MagX, MagY, MagZ; // 磁场三值
    std::memcpy(&MagX, &ProcessedData[MAG_BASE], FLOAT_SIZE);
    std::memcpy(&MagY, &ProcessedData[MAG_BASE + FLOAT_SIZE], FLOAT_SIZE);
    std::memcpy(&MagZ, &ProcessedData[MAG_BASE + 2 * FLOAT_SIZE], FLOAT_SIZE);
    JY901SDataMag->setText(QString("X%1  Y%2  Z%3")
                               .arg(QString::number(MagX),
                                    QString::number(MagY),
                                    QString::number(MagZ)));

    float AccelX, AccelY, AccelZ; // 加速度三值
    std::memcpy(&AccelX, &ProcessedData[ACCEL_BASE], FLOAT_SIZE);
    std::memcpy(&AccelY, &ProcessedData[ACCEL_BASE + FLOAT_SIZE], FLOAT_SIZE);
    std::memcpy(&AccelZ, &ProcessedData[ACCEL_BASE + 2 * FLOAT_SIZE],
                FLOAT_SIZE);
    JY901SDataAcc->setText(QString("X%1  Y%2  Z%3")
                               .arg(QString::number(AccelX, 'f', 3),
                                    QString::number(AccelY, 'f', 3),
                                    QString::number(AccelZ, 'f', 3)));

    float GyroX, GyroY, GyroZ; // 加速度三值
    std::memcpy(&GyroX, &ProcessedData[GYRO_BASE], FLOAT_SIZE);
    std::memcpy(&GyroY, &ProcessedData[GYRO_BASE + FLOAT_SIZE], FLOAT_SIZE);
    std::memcpy(&GyroZ, &ProcessedData[GYRO_BASE + 2 * FLOAT_SIZE], FLOAT_SIZE);
    JY901SDataGyro->setText(QString("X%1  Y%2  Z%3")
                                .arg(QString::number(GyroX, 'f', 3),
                                     QString::number(GyroY, 'f', 3),
                                     QString::number(GyroZ, 'f', 3)));
  }
}

//暂不使用
void DataDisplayWidget::SaveToFile(const QString &path){
    QFile output(path);
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream ts(&output);
    ts << "VFdGeWFXUnZaekl3TURJd05ESTE=\n";

    output.close();
}
