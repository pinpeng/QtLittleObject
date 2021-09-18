#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <setgamedialog.h>

GameWindow::GameWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::GameWindow),
    numFont("黑体",15,QFont::Bold,true),
    gameOverFont("黑体",50,QFont::Bold,true),
    rectPen(Qt::black)
{
  ui->setupUi(this);

  columnCount = 10;
  lineCount = 10;
  boomCount = 10;

  gameData.InitGameData(columnCount,lineCount,boomCount);

  connect(ui->actionrestart,&QAction::triggered,this,&GameWindow::restart);
  connect(ui->actionconfig,&QAction::triggered,this,&GameWindow::setWindow);
}

GameWindow::~GameWindow()
{
  delete ui;
}

void GameWindow::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  menuHeight = ui->menubar->size().height();

  int winHeight = this->geometry().height();
  int winWidth = this->geometry().width();

  cubeHeight = (winHeight-menuHeight)*1.0/lineCount;
  cubeWidth = winWidth*1.0/columnCount;

  for(int i=0;i<lineCount;i++){
      for(int j=0;j<columnCount;j++){
          QRect rect(cubeWidth*i,menuHeight+cubeHeight*j,cubeWidth,cubeHeight);
          painter.setPen(rectPen);
          painter.drawRect(rect);

          if(st[i][j]){
            if(gameData.cell[i][j]==9){
                painter.fillRect(rect,QBrush(Qt::red));
              }
            painter.setFont(numFont);
            painter.drawText(rect.center(),QString::number(gameData.cell[i][j]));
          }

    }
    }
  if(gameOver){
      painter.setFont(gameOverFont);
      painter.drawText(rect().center().x()/2,rect().center().y()
                       ,"GameOver");
    }
  else if(gameClear){
      painter.setFont(gameOverFont);
      painter.drawText(rect().center().x()/2,rect().center().y()
                       ,"GameClear");
    }
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
  if(gameOver||gameClear) return;
  int x = event->x()/cubeWidth;
  int y = (event->y()-menuHeight)/cubeHeight;

  qDebug()<<x<<" "<<y<<endl;

  bfs(x,y);

  if(gameData.cell[x][y]==9){
      gameOver = true;
    }
  else{
      int count = 0;
      for(int i=0;i<columnCount;i++){
          for(int j=0;j<lineCount;j++){
              if(st[i][j]==false) count++;
            }
        }
      if(count==boomCount)
         gameClear = true;
    }

  update();
}

void GameWindow::bfs(int x, int y)
{
  if(st[x][y]) return;

  st[x][y] = true;

  if(gameData.cell[x][y] == 0){
      if(x>0) bfs(x-1,y);
      if(x<columnCount-1) bfs(x+1,y);
      if(y>0) bfs(x,y-1);
      if(y<lineCount-1) bfs(x,y+1);
    }

}

void GameWindow::restart()
{
  gameClear = false;
  gameOver = false;

  memset(st,0,sizeof st);
  gameData.InitGameData(columnCount,lineCount,boomCount);

  update();
}

void GameWindow::setWindow()
{
  SetGameDialog dialog(this);

  if(dialog.exec()==QDialog::Accepted){
      columnCount = std::min(dialog.GetColumnCount(),20);
      lineCount = std::min(dialog.GetLineCount(),20);
      boomCount = std::min(dialog.GetBoomCount(),400);

      restart();
    }
}


