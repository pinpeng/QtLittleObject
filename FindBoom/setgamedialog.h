#ifndef SETGAMEDIALOG_H
#define SETGAMEDIALOG_H

#include <QDialog>

namespace Ui {
  class SetGameDialog;
}

class SetGameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SetGameDialog(QWidget *parent = nullptr);
  ~SetGameDialog();

  int GetColumnCount();
  int GetLineCount();
  int GetBoomCount();
private slots:
  void onOkClicked();
private:
  Ui::SetGameDialog *ui;
};

#endif // SETGAMEDIALOG_H
