#ifndef DRAGTREEWIDGET_H
#define DRAGTREEWIDGET_H

#include <QTreeWidget>
#include <QLabel>

class DragTreeWidget : public QTreeWidget
{
  Q_OBJECT
public:
  DragTreeWidget(QWidget* parent = nullptr);
private:
  //初始化函数
  void initTreeWidget();

  void mousePressEvent(QMouseEvent* ev) override;
  void mouseMoveEvent(QMouseEvent* ev) override;
  void mouseReleaseEvent(QMouseEvent* ev) override;
private:
  QLabel label;
  QTreeWidgetItem* pSource;
  QTreeWidgetItem* pParent;
  int originIndex;
  bool isJudged;
};

#endif // DRAGTREEWIDGET_H
