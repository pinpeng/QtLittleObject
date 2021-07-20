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
  //用来显示label，显性表示拖拽
  QLabel label;
  //表示被拖拽的item
  QTreeWidgetItem* pSource;
  //表示被拖拽的item的父节点
  QTreeWidgetItem* pParent;
  //表示被拖拽的item在父节点中的索引
  int originIndex;
  //用于判断在mouseMoveEvent中是否已经移除了组件
  bool isJudged;
};

#endif // DRAGTREEWIDGET_H
