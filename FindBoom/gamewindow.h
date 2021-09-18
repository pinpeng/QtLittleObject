#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <gamedata.h>
#include <QPen>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
  Q_OBJECT

public:
  GameWindow(QWidget *parent = nullptr);
  ~GameWindow();
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  bool st[100][100];
private:
  void bfs(int x,int y);
private slots:
  void restart();
  void setWindow();
private:
  Ui::GameWindow *ui;
  GameData gameData;
  int columnCount;
  int lineCount;
  int boomCount;
  int menuHeight;
  double cubeHeight;
  double cubeWidth;

  QFont numFont;
  QFont gameOverFont;
  QPen rectPen;

  bool gameOver;
  bool gameClear;
};
#endif // GAMEWINDOW_H
