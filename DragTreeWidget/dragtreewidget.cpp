#include "dragtreewidget.h"
#include <QDebug>
#include <QMouseEvent>

DragTreeWidget::DragTreeWidget(QWidget *parent)
  :QTreeWidget(parent),
    label(this),
    pSource(nullptr)
{
  initTreeWidget();
  setHeaderHidden(true);
  label.resize(100,30);
  label.setText("");
  label.hide();
}

void DragTreeWidget::initTreeWidget()
{
  for(int i=0;i<10;i++){
      QTreeWidgetItem* pTopItem = new QTreeWidgetItem(this);
      pTopItem->setText(0,QString::number(114514+i));
      addTopLevelItem(pTopItem);
    }
  for(int i=0;i<10;i++){
      QTreeWidgetItem* pChildItem = new QTreeWidgetItem(topLevelItem(0));
      pChildItem->setText(0,QString::number(191981+i));
      topLevelItem(0)->addChild(pChildItem);
    }
}

void DragTreeWidget::mousePressEvent(QMouseEvent *ev)
{
  qDebug()<<"in mousePressEvent"<<endl;
  pSource = itemAt(ev->pos());
  qDebug()<<pSource->text(0)<<endl;
  if(pSource->parent()){
      qDebug()<<"source parent is "<<pSource->parent()->text(0)<<endl;
    }

  label.setText(pSource->text(0));

  isJudged = false;

  QTreeWidget::mousePressEvent(ev);
}

void DragTreeWidget::mouseMoveEvent(QMouseEvent *ev)
{
  if(pSource==nullptr){
      QTreeWidget::mouseMoveEvent(ev);
      return;
    }

    qDebug()<<"in mouseMoveEvent"<<endl;

  label.show();
  label.move(ev->pos());

  if(isJudged==false){
      isJudged = true;
      if(pSource->parent()){
          qDebug()<<"isSubItem"<<endl;
          pParent = pSource->parent();

          originIndex = pParent->indexOfChild(pSource);

          pParent->takeChild(originIndex);
        }
      else{
          qDebug()<<"isMainItem"<<endl;
          pParent = nullptr;
          takeTopLevelItem(indexOfTopLevelItem(pSource));
        }

      qDebug()<<"source = "<<pSource->text(0)<<endl;
    }
}

void DragTreeWidget::mouseReleaseEvent(QMouseEvent *ev)
{
  qDebug()<<"in mouseReleaseEvent"<<endl;

    label.hide();

  QTreeWidgetItem* pTarget = itemAt(ev->pos());

  if(pTarget==nullptr){
      if(pParent){
          pParent->insertChild(originIndex,pSource);
        }
      else{
          addTopLevelItem(pSource);
        }

      setCurrentItem(pSource);
      return;
    }

//  qDebug()<<"is child = "<<isChild<<endl;
  if(pTarget->parent()){
      qDebug()<<"PTarget parent = "<<pTarget->parent()->text(0)<<endl;
    }

  //如果是父节点
  if(pTarget->parent()==nullptr){
      if(pParent){
          pTarget->addChild(pSource);
        }
      else{
          insertTopLevelItem(indexOfTopLevelItem(pTarget)+1,pSource);
        }
    }
  //如果是子节点
  else{
      if(pParent){
          QTreeWidgetItem* parent = pTarget->parent();
          parent->insertChild(parent->indexOfChild(pTarget)+1,pSource);
        }
      else{

        }
    }
        setCurrentItem(pSource);
}
