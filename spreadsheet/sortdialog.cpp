#include "sortdialog.h"
#include "ui_sortdialog.h"

SortDialog::SortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortDialog)
{
    ui->setupUi(this);
    ui->groupBox_2->hide();
    ui->groupBox_3->hide();
    setColumnRange('A', 'Z');

}

SortDialog::~SortDialog()
{
    delete ui;
}

void SortDialog::setColumnRange(QChar first, QChar last)
{
    ui->comboBox->clear();
    ui->comboBox_3->clear();
    ui->comboBox_5->clear();
    ui->comboBox_3->addItem(tr("None"));
    ui->comboBox_5->addItem(tr("None"));
#if 1
    ui->comboBox->setMinimumSize(ui->comboBox_3->sizeHint());

    QChar ch = first;
    while (ch <= last) {
        ui->comboBox->addItem(QString(ch));
        ui->comboBox_3->addItem(QString(ch));
        ui->comboBox_5->addItem(QString(ch));
        ch = ch.unicode() + 1;
    }
  #endif
}
