#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(const QString& initialFolder, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->hide();
    if (!initialFolder.isEmpty())
        ui->tableWidget->UpdateTable(initialFolder);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ApplyButton_clicked()
{
    DropTableWidget *table = ui->tableWidget;
    Tagger tagger;

    for (int i = 0; i < table->rowCount(); ++i) {
        tagger.UpdateTagsInFile({
            table->item(i, 0)->text(),
            table->item(i, 1)->text(),
            table->item(i, 2)->text(),
            table->item(i, 3)->text(),
            table->item(i, 4)->text(),
            table->item(i, 5)->text()
        });
    }
    ui->statusbar->showMessage("Change was applied to files!");
}
