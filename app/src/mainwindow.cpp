#include <QtWidgets/QDialog>
#include <QtWidgets/QStyleFactory>
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
        int year = table->item(i, 4)->text().toInt();
        if (year < 0)
            year = 0;
        tagger.UpdateTagsInFile({
            table->item(i, 0)->text(),
            table->item(i, 1)->text(),
            table->item(i, 2)->text(),
            table->item(i, 3)->text(),
            static_cast<unsigned int>(year),
            table->item(i, 5)->text()
        });
    }
    ui->textEdit->WriteToLog("Changes was applied to files!");
    ui->statusbar->showMessage("Changes was applied to files!");
}

QPair<QPalette, QString> getStyle() {
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;

    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    return {darkPalette, "QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }"};
}

void MainWindow::ChangeTheme(bool toggler) {
    static auto basicTheme = qApp->styleSheet();
    static auto basicPalette = qApp->palette();
    static auto darkTheme = getStyle();

    if (toggler) {
        qApp->setPalette(darkTheme.first);
        qApp->setStyleSheet(darkTheme.second);
        return;
    }
    qApp->setPalette(basicPalette);
    qApp->setStyleSheet(basicTheme);
}
