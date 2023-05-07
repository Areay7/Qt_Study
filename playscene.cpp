#include "playscene.h"


//PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow{parent}
//{

//}


PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第%1关").arg(levelNum);
    qDebug() << str;
    this ->levelIndex = levelNum;

    // 初始化游戏场景
    // 设置固定大小
    this -> setFixedSize(320,588);

    // 设置图标
    this -> setWindowIcon(QPixmap(":/res/Coin0001.png"));

    // 设置标题
    this -> setWindowTitle("翻金币场景");

    // 创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    bar->setNativeMenuBar(false);

    // 创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    // 创建退出菜单项
    QAction * quitAction = startMenu->addAction("退出");

    // 点击退出 实现退出游戏
    connect(quitAction, &QAction::triggered, [=](){
        this -> close();
    });

    // 添加音效资源
    // 返回按钮音效
    QSoundEffect * backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    // 翻金币音效
    QSoundEffect * flipSound = new QSoundEffect(this);
    flipSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    // 胜利按钮音效
    QSoundEffect * winSound = new QSoundEffect(this);
    winSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));

    // 返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn -> setParent(this);
    backBtn -> move(this -> width() - backBtn -> width(), this -> height() - backBtn -> height());

    // 点击返回
    connect(backBtn, &MyPushButton::clicked, [=](){
                qDebug() << "点击了返回按钮";
         // 播放返回按钮音效
        backSound -> play();

        // 告诉主场景  返回了，  主场景监听ChooseLevelScene的返回按钮
        // 延时返回
        QTimer::singleShot(230,[=](){
            emit this -> ChooseSceneBack();
        });
    });

    // 显示当前关卡数
    QLabel * label = new QLabel;
    label -> setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPixelSize(25);
    QString str1 = QString("Level:%1").arg(this->levelIndex);
    // 将字体设置到标签控件中
    label -> setFont(font);
    label -> setText(str1);
    label -> setGeometry(30, this -> height() - 50, 120, 50);


    dataConfig config;
    // 初始化每个关卡的二维数组
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this -> gameArray[i][j] = config.mData[(this->levelIndex)][i][j];
        }
    }

    // 胜利图片显示
    QLabel * winLael = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLael -> setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLael -> setPixmap(tmpPix);
    winLael -> setParent(this);
    winLael -> move((this -> width() - tmpPix.width()) * 0.5 , - tmpPix.height());



    // 显示金币背景图案
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            // 绘制背景图
            QLabel * label = new QLabel;
            QPixmap pix= QPixmap(":/res/BoardNode.png");
            label -> setGeometry(0,0,pix.width(),pix.height());
            label -> setPixmap(pix);
            label -> setParent(this);
            label -> move(57 + i*50, 200 + j*50);

            // 创建金币
            QString str;
            if(this -> gameArray[i][j] == 1)
            {
                // 显示金币
                str =   ":/res/Coin0001.png";
            }
            else
            {
                str =   ":/res/Coin0008.png";
            }

            MyCoin * coin = new MyCoin(str);
            coin -> setParent(this);
            coin -> move(59 + i*50, 204 + j*50);

            // 给金币的属性赋值
            coin -> posX = i;
            coin -> posY = j;
            coin -> flag = this -> gameArray[i][j];  // 1 正面  0 反面

            // 将金币放入到金币的二维数组中，便于后期维护
            coinBtn[i][j] = coin;

            // 点击金币 进行翻转
            connect(coin, &MyCoin::clicked, [=](){
                // 播放翻金币的音效
            flipSound -> play();

                //  点击按钮时 将所有按钮禁用
                        for(int i = 0; i < 4; i++)
                        {
                            for(int j = 0; j < 4; j++)
                            {
                                this -> coinBtn[i][j] -> notPress = true;
                            }
                        }
                coin -> changeFlag();
                this -> gameArray[i][j] = this -> gameArray[i][j] == 0 ? 1 : 0;

            // 翻转周围金币
                // 延时翻转
                QTimer::singleShot(250,[=](){
                    if(coin -> posX + 1 <= 3)  // 周围右侧金币翻转的条件
                    {
                        coinBtn[coin->posX+1][coin->posY] -> changeFlag();
                        this -> gameArray[coin->posX+1][coin->posY] = this -> gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }

                    if(coin -> posX - 1 >= 0)  // 周围左侧金币翻转的条件
                    {
                        coinBtn[coin->posX-1][coin->posY] -> changeFlag();
                        this -> gameArray[coin->posX-1][coin->posY] = this -> gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                    }

                    if(coin -> posY + 1 <= 3)  // 周围上侧金币翻转的条件
                    {
                        coinBtn[coin->posX][coin->posY+1] -> changeFlag();
                        this -> gameArray[coin->posX][coin->posY+1] = this -> gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
                    }

                    if(coin -> posY - 1 >= 0)  // 周围下侧金币翻转的条件
                    {
                        coinBtn[coin->posX][coin->posY-1] -> changeFlag();
                        this -> gameArray[coin->posX][coin->posY-1] = this -> gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                    }

                    // 翻转动画完成 重新开启按钮
                        for(int i = 0; i < 4; i++)
                        {
                            for(int j = 0; j < 4; j++)
                            {
                                this -> coinBtn[i][j] -> notPress = false;
                            }
                        }

//                    // 判断是否胜利
                    this -> isWin = true;
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            if(coinBtn[i][j] -> flag == false) // 只要有一个是反面，就算失败
                            {
                                this -> isWin = false;
                                break;
                            }
                        }
                    }
                    if(this -> isWin == true)
                    {
                        // ✌胜利
                        // 播放胜利音效
                        winSound -> play();
                        qDebug() << "游戏胜利";

                        // 将所有按钮的胜利标志改为true; 如果再次点击按钮，将直接return，不作响应
                        for(int i = 0; i < 4; i++)
                        {
                            for(int j = 0; j < 4; j++)
                            {
                                this -> coinBtn[i][j] -> notPress = true;

                            }
                        }
                        //  将胜利的图片移下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLael,"geometry");
                        // 设置时间间隔
                        animation -> setDuration(1000);
                        // 设置开始位置
                        animation -> setStartValue(QRect(winLael->x(),winLael->y(),winLael->width(),winLael->height()));
                        //                        // 设置结束位置
                        animation -> setEndValue(QRect(winLael->x(),winLael->y()+205,winLael->width(),winLael->height()));
                        // 设置缓和曲线
                        animation -> setEasingCurve(QEasingCurve::OutBounce);
                        // 执行动画
                        animation -> start();
                    }
                });
            });
        }
    }


}


// 重写paintEvent事件  画背景图
void PlayScene::paintEvent(QPaintEvent *)
{
    // 加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 加载标题
    // 画背景上的图标
    pix.load(":/res/Title.png");

    // 图标缩放
    pix = pix.scaled(pix.width() * 1.05, pix.height() * 1.05);

    painter.drawPixmap(15,30,pix);
}
