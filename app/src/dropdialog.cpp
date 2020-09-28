#include "dropdialog.h"
#include "ui_dropdialog.h"

DropDialog::DropDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DropDialog) {
    ui->setupUi(this);
}

DropDialog::~DropDialog() {
    delete ui;
}

void DropDialog::accept() {
    emit ReturnValues(ui->lineEdit->text().prepend(" ").prepend(ui->comboBox->currentText()),
                      ui->checkBox->isChecked(),
                      ui->checkBox_2->isChecked());
    QDialog::accept();
}
