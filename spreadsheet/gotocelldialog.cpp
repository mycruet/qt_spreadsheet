#include "gotocelldialog.h"
#include "ui_gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoToCellDialog)
{
    ui->setupUi(this);
}

GoToCellDialog::~GoToCellDialog()
{
    delete ui;
}
 QString GoToCellDialog::getlineEdit()
 {

     return ui->lineEdit->text();

 }
