#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initWidget();
    initNum();
    setLabel();
    updatejpg();

}

MainWindow::~MainWindow()
{

}



void MainWindow::initWidget()
{
    this->mainwidget=new QWidget(this);
    this->setCentralWidget(mainwidget);
    this->firstwidget=new QWidget(mainwidget);
    this->secondwidget=new QWidget(mainwidget);





    //中心窗口采用垂直布局，分为上下两块，上面的是信息显示和附加功能，下面的是数字界面
    this->mainlayout=new QVBoxLayout(mainwidget);
    this->mainlayout->addWidget(firstwidget);
    this->mainlayout->addWidget(secondwidget);
    //设置mainwidget背景
    mainwidget->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/img/mainbg.jpg")));
    mainwidget->setPalette(palette);







    //在上面，采用横向布局，显示信息
    this->firstlayout=new QHBoxLayout(firstwidget);
    this->firstwidget->setLayout(firstlayout);
    this->welcomelabel=new QLabel(tr("欢迎来到2048"),this->firstwidget);

    welcomelabel->setAlignment(Qt::AlignCenter);
    welcomelabel->setFont(QFont("Microsoft YaHei", 12 ,QFont::Bold));
    welcomelabel->setStyleSheet("color:orange");

    this->regret=new QPushButton();
    this->regret->setText(tr("后退到上一步"));
    this->regret->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    this->regret->setFont(QFont("Microsoft YaHei", 12 ,QFont::Bold));
    this->regret->setStyleSheet("color:grey");
    connect(regret,SIGNAL(clicked()),this,SLOT(regretslot()));

    this->firstlayout->addWidget(welcomelabel);
    firstlayout->addStretch();
    firstlayout->addStretch();
    this->firstlayout->addWidget(regret);






    //在下面，采用网格布局。在setLabel（）里，数字numLabel会布局到这里
    secondlayout=new QGridLayout(secondwidget);
    this->secondwidget->setLayout(secondlayout);
    //设置secondwidget背景
    secondwidget->setStyleSheet(":/img/bg.jpg)");





    //设置所有窗口的大小
    this->resize(350,400);
    mainwidget->resize(350,400);
    firstwidget->resize(340,100);
    secondwidget->resize(340,340);


}


//初始化game数组
void MainWindow::initNum()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            game[i][j]=0;
        }
    }
    insertNewNumber(game);
}


//将主要数组game备份到pre数组，有两个功能，一个是可以后退一步
//另一个是检测当前的动作是否是无效操作
void MainWindow::CopytoPre()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            pre[i][j]=game[i][j];
        }
    }
}



//将alllabel数组用于表格布局，这是游戏的主体
void MainWindow::setLabel()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->alllabel[i][j]=new QLabel(secondwidget);
            secondlayout->addWidget(alllabel[i][j],i,j,1,1);
            this->alllabel[i][j]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
        }
    }

}




//此函数用于把game数组中的数字更新显示在表格布局中
void MainWindow::updatejpg()
{
    QImage *image0=new QImage(":/img/0.jpg");
    QImage *image2=new QImage(":/img/2.jpg");
    QImage *image4=new QImage(":img/4.jpg");
    QImage *image8=new QImage(":/img/8.jpg");
    QImage *image16=new QImage(":/img/16.jpg");
    QImage *image32=new QImage(":/img/32.jpg");
    QImage *image64=new QImage(":/img/64.jpg");
    QImage *image128=new QImage(":/img/128.jpg");
    QImage *image256=new QImage(":/img/256.jpg");
    QImage *image512=new QImage(":/img/512.jpg");
    QImage *image1024=new QImage(":/img/1024.jpg");
    QImage *image2048=new QImage(":/img/2048.jpg");


    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            switch(game[i][j])
            {
            case 0:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image0));break;
            case 2:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image2));break;
            case 4:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image4));break;
            case 8:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image8));break;
            case 16:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image16));break;
            case 32:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image32));break;
            case 64:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image64));break;
            case 128:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image128));break;
            case 256:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image256));break;
            case 512:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image512));break;
            case 1024:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image1024));break;
            case 2048:alllabel[i][j]->setPixmap(QPixmap::fromImage(*image2048));break;
            }
        }

}





//用鼠标按下和释放之间的坐标差，判断上下左右
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    pressPos=e->pos();
}


void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    releasePos=e->pos();
    int rx=releasePos.x()-pressPos.x();
    int ry=releasePos.y()-pressPos.y();
    if(abs(rx)>abs(ry))
    {
        if(rx>0)
        {
            CopytoPre();
            leftToRight();
        }
        else
        {
            CopytoPre();
            rightToLeft();
        }
    }
    else
    {
        if(ry>0)
        {
           CopytoPre();
           upToDown();
        }
        else
        {
           CopytoPre();
           downToUp();
        }
    }
    judgeGame();
    judgeFail();
    updatejpg();



}



//最初设计为解决向右移动时，单行的移动问题
//但其余三种情况最后利用数组的转换，都复用了这一核心函数
void MainWindow::solveOneLine(int emptyCount)
{
        switch (emptyCount)
        {
        case 0: full(); break;
        case 1: emptyOne(); break;
        case 2: emptyTwo(); break;
        case 3: emptyThree(); break;
        case 4: break;
        }
}



//向右移动
void MainWindow::leftToRight()
{
        int emptyCount = 0;
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        line[j] = game[i][j];
                        if (game[i][j] == 0) { emptyCount++; }//统计一行中有多少个0，0代表空格
                }
                //printf("\n");
                solveOneLine(emptyCount);	//进行合并
                                                                        //printf("******%d*******", emptyCount);
                emptyCount = 0;
                //写入到game数组
                for (int k = 0; k < 4; k++)
                {
                        game[i][k] = line[k];
                }
        }

}

//向左移动，通过将game数组每行的数倒过来赋值给line,实现复用
void MainWindow::rightToLeft()
{
        int emptyCount = 0;
        for (int i = 0; i < 4; i++)
        {
                line[0] = game[i][3];
                line[1] = game[i][2];
                line[2] = game[i][1];
                line[3] = game[i][0];
                for (int m = 0; m < 4; m++)
                {
                        if (line[m] == 0) { emptyCount++; }//统计一行中有多少个0，0代表空格
                }
                solveOneLine(emptyCount);	//进行合并
                                                                        //printf("******%d*******",emptyCount);
                emptyCount = 0;
                //将line中数据写入到game数组中
                game[i][0] = line[3];
                game[i][1] = line[2];
                game[i][2] = line[1];
                game[i][3] = line[0];
        }

}

//向下移动，通过将game数组每列的数倒过来赋值给line,实现复用
void MainWindow::upToDown()
{
        int emptyCount = 0;
        for (int j = 0; j < 4; j++)
        {
                for (int i = 0; i < 4; i++)
                {
                        line[i] = game[i][j];
                        if (line[i] == 0) { emptyCount++; }//统计一行中有多少个0，0代表空格
                }
                solveOneLine(emptyCount);	//进行合并
                                                                        //printf("******%d*******",emptyCount);
                emptyCount = 0;
                //将line中数据写入到game数组中
                for (int k = 0; k < 4; k++) //将合并后的结果写入
                {
                        game[k][j] = line[k];
                }
        }
}

//向上移动，通过将game数组每列的数倒过来赋值给line,实现复用
void MainWindow::downToUp()
{
        int emptyCount = 0;
        for (int j = 0; j < 4; j++)
        {
                line[3] = game[0][j];
                line[2] = game[1][j];
                line[1] = game[2][j];
                line[0] = game[3][j];
                for (int i = 0; i < 4; i++)
                {
                        if (line[i] == 0) { emptyCount++; }//统计一行中有多少个0，0代表空格
                }
                solveOneLine(emptyCount);	//进行合并
                                                                        //printf("******%d*******", emptyCount);
                emptyCount = 0;
                //将line中数据写入到game数组中
                game[3][j] = line[0];
                game[2][j] = line[1];
                game[1][j] = line[2];
                game[0][j] = line[3];
        }
}



//这一行都是非零数字
void MainWindow::full()
{
        bool diffFlag = true;
        //四个都相同
        if (line[0] == line[1] && line[1] == line[2] && line[2] == line[3])
        {
                line[2] = line[0] * 2;
                line[3] = line[0] * 2;
                line[0] = 0;
                line[1] = 0;
                return;
        }


        //四个都不相同,先是用for循环判断
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        if (line[i] == line[j]) { diffFlag = false; }
                }
        }
        if (diffFlag == true)
        {
                return;
        }



        //有两对相同
        if (line[0] == line[1] && line[2] == line[3] && line[1] != line[2])
        {
                line[2] = 2 * line[1];
                line[3] = 2 * line[3];
                line[0] = 0;
                line[1] = 0;
                return;
        }

        //有连续三个相同
        if (line[0] == line[1] && line[1] == line[2])
        {
                line[2] = line[1] + line[0];
                line[1] = line[0];
                line[0] = 0;
                return;
        }
        if (line[1] == line[2] && line[2] == line[3])
        {
                line[3] = line[1] + line[2];
                line[2] = line[1];
                line[1] = line[0];
                line[0] = 0;
                return;
        }


        //仅有一对相同
        if (line[0] == line[1]) { line[1] = 2 * line[1]; line[0] = 0; return; }
        if (line[1] == line[2]) { line[2] = 2 * line[2]; line[1] = line[0]; line[0] = 0; return; }
        if (line[2] == line[3]) { line[3] = 2 * line[3]; line[2] = line[1]; line[1] = line[0]; line[0] = 0; return; }

}

//有一个空格0
void MainWindow::emptyOne()
{
        int second = 0;
        int third = 0;
        int forth = 0;
        //把所有数据都依次移到最后三格
        if (line[0] == 0)
        {
                second = line[1];
                third = line[2];
                forth = line[3];
        }

        if (line[1] == 0)
        {
                second = line[0];
                third = line[2];
                forth = line[3];
        }

        if (line[2] == 0)
        {
                second = line[0];
                third = line[1];
                forth = line[3];
        }

        if (line[3] == 0)
        {
                second = line[0];
                third = line[1];
                forth = line[2];
        }


        //合并最后三个数据
        if (forth == third)
        {
                forth = forth * 2;
                third = second;
                second = 0;
        }
        else if (second == third)
        {
                third = third * 2;
                second = 0;
        }

        //把数据回写到line数组
        line[0] = 0;
        line[1] = second;
        line[2] = third;
        line[3] = forth;
}

//有两个空格0
void MainWindow::emptyTwo()
{
        int third = 0;
        int forth = 0;
        for (int i = 0; i <= 4; i++)
        {
                if ((line[i] != 0))
                {
                        third = line[i];
                        i++;
                        forth = line[0] + line[1] + line[2] + line[3] - third;
                        break;
                }
        }
        line[0] = 0;
        line[1] = 0;
        line[2] = third;
        line[3] = forth;
        if (line[2] == line[3])
        {
                line[2] = 0;
                line[3] = line[3] * 2;
        }
        else
        {
                return;
        }
}

//有三个空格0
void MainWindow::emptyThree()
{
        line[3] = line[0] + line[1] + line[2] + line[3];
        line[0] = 0;
        line[1] = 0;
        line[2] = 0;
}




/*插入随机数*/
void MainWindow::insertNewNumber(int board[4][4]) {
        int row, column;
        int index, availableSquares = 0;
        // count vacant squares
        for (row = 0; row < 4; row = row + 1)
        {
                for (column = 0; column < 4; column = column + 1)
                {
                        if (board[row][column] == 0)
                        {
                                availableSquares = availableSquares + 1;
                        }
                }
        }


        // randomly pick a vacant square
        index = rand() % availableSquares;

        for (row = 0; row < 4; row = row + 1)
        {
                for (column = 0; column < 4; column = column + 1)
                {
                        if (board[row][column] == 0)
                        {
                                if (index == 0)
                                {
                                        if (rand() % 10 == 0)
                                        {
                                                board[row][column] = 4;
                                        }
                                        else {
                                                board[row][column] = 2;
                                        }
                                        return;
                                }
                                index = index - 1;
                        }
                }
        }
}





//判断失败和无效操作，一个动作后game和pre相同那就是无效(flag=16)
//没有空格判定失败
void MainWindow::judgeFail()
{

    int flag = 0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(game[i][j]==pre[i][j])
            {
                flag++;
            }
        }
    }



    int availableSquares = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (game[i][j] == 0)
            {
                availableSquares++;
            }
        }
    }



    if(flag==16 && availableSquares != 0)
    {
        QMessageBox::information(NULL,"提示","这个方向没有任何格子可以合并,您将无法后退一格");

    }


    if (flag != 16 && availableSquares != 0)
    {
        insertNewNumber(game);
    }



    if(availableSquares == 0)
    {
        QMessageBox::information(NULL,"game over","game over");
        initNum();
    }



}




//判断获胜，出现2048弹出获胜消息框
void MainWindow::judgeGame()
{
    int flag = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (game[i][j] == 2048)
            {
                flag = 1;
                break;
            }

        }
    }

    if (flag == 1)
    {
        QMessageBox::information(NULL,"win","You win the game!!!");
        initNum();
    }

}




//后退一步，核心是把pre数组写入game数组
void MainWindow::regretslot()
{
    int flag = 0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(game[i][j]==pre[i][j])
            {
                flag++;
            }
        }
    }
    if(flag==16)
    {
        QMessageBox::information(NULL,"提示","无法后退一步");
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                game[i][j]=pre[i][j];

            }
        }
        updatejpg();
        QMessageBox::information(NULL,"提示","已经后退一步");
    }

}
