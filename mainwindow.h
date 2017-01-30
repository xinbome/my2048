#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include<QDebug>
#include<time.h>
#include<QPoint>
#include<QMouseEvent>
#include<QQueue>
#include<QMessageBox>
#include<QPainter>
#include<QLabel>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QPalette>
#include<QHBoxLayout>
#include<QTextCodec>
#include<QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initWidget();
    void setLabel();
    void updatejpg();
    void initNum();
    void CopytoPre();


    void leftToRight();
    void rightToLeft();
    void upToDown();
    void downToUp();


    void solveOneLine(int emptyCount);
    void full();
    void emptyOne();
    void emptyTwo();
    void emptyThree();
    void insertNewNumber(int board[4][4]);

    void judgeFail();
    void judgeGame();

private:
    QLabel *alllabel[4][4];
    QPoint pressPos;
    QPoint releasePos;
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    QWidget *mainwidget;
    QWidget *firstwidget;
    QWidget *secondwidget;
    QVBoxLayout *mainlayout;
    QHBoxLayout *firstlayout;
    QGridLayout *secondlayout;

    int game[4][4];
    int pre[4][4];
    int line[4];


    QLabel *welcomelabel;
    QPushButton *regret;

private slots:
    void regretslot();

};

#endif // MAINWINDOW_H
