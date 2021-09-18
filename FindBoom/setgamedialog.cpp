#include "setgamedialog.h"
#include "ui_setgamedialog.h"

SetGameDialog::SetGameDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SetGameDialog)
{
  ui->setupUi(this);

  connect(ui->confirmButton,&QPushButton::clicked,this,&SetGameDialog::onOkClicked);
}

SetGameDialog::~SetGameDialog()
{
  delete ui;
}

int SetGameDialog::GetColumnCount()
{
  return ui->columnCountEdit->text().toInt();
}

int SetGameDialog::GetLineCount()
{
  return ui->lineCountEdit->text().toInt();
}

int SetGameDialog::GetBoomCount()
{
  return ui->boomCountEdit->text().toInt();
}

void SetGameDialog::onOkClicked()
{
  bool ok;

  ui->columnCountEdit->text().toInt(&ok);
  ui->lineCountEdit->text().toInt(&ok);
  ui->boomCountEdit->text().toInt(&ok);

  if(ok){
      accept();
    }
}
