#pragma once
#include <QDialog>
#include "manager.h"

namespace Ui {
class ChangeDialog;
}

class ChangeDialog : public QDialog {
    Q_OBJECT
public:
    explicit ChangeDialog(QWidget *parent = nullptr);
    ~ChangeDialog();

private slots:
    void on_submitDialogBox_accepted();

private:
    Ui::ChangeDialog *ui;

    //Вспомогательная функция конвертации qString в double
    double qStringToDouble(const QString & value);
};
