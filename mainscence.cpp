#include "mainscence.h"
#include "ui_mainscence.h"

MainScence::MainScence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScence)
{
    ui->setupUi(this);

    // 配置主场景

    // 设置固定大小
    setFixedSize(320,588);

    // 设置图标
    setWindowIcon(QIcon("logo.icns"));

    // 设置标题
    setWindowTitle("翻金币主场景");

    // 退出按钮实现
    connect(ui -> actionquit, &QAction::triggered, [=](){
        this -> close();
    });

    // 准备开始的音效
    QSoundEffect * startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    startSound -> setLoopCount(-1);   // 设置循环   -1代表无限循环
    startSound->play();


    // 开始按钮
    MyPushButton * startBtn =  new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn -> setParent(this);
    startBtn -> move(this -> width() * 0.5 - startBtn -> width() * 0.5, this -> height() * 0.7);

    // 实例化，选择关卡场景
    chooseScene = new ChooseLevelScene;

    // 监听选择关卡的返回按钮的信号
    connect(chooseScene, &ChooseLevelScene::ChooseSceneBack, [=](){
        this->setGeometry(chooseScene -> geometry());
        chooseScene -> hide();  //  将选择关卡场景，隐藏掉
        this -> show();         // 重新显示主场景
    });

    connect(startBtn, &MyPushButton::clicked, [=](){
//        qDebug() << "点击了开始";

        // 播放开始音效资源
        startSound->play();


        // 弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        // 延时进入到选择关卡场景
        QTimer::singleShot(350,this,[=](){
            // 设置chooseScene场景的位置
            chooseScene -> setGeometry(this->geometry());

            // 进入到关卡场景中
            // 将自身隐藏
            this -> hide();
            // 显示选择关卡
            chooseScene -> show();
        });
    });
}

// 重写paintEvent事件  画背景图
void MainScence::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 画背景上的图标
    pix.load(":/res/Title.png");

    // 图标缩放
    pix = pix.scaled(pix.width() * 1.05, pix.height() * 1.05);

    painter.drawPixmap(15,30,pix);
}

MainScence::~MainScence()
{
    delete ui;
}

