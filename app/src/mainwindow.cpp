#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QGridLayout *layout;

    ui->setupUi(this);
    layout = new QGridLayout(ui->frame);
    ui->frame->setLayout(layout);
    ui->frame->layout()->addWidget(ui->drop_label);
    ui->frame->layout()->setAlignment(ui->drop_label, Qt::AlignCenter);
    QObject::connect(ui->frame, &FileDropFrame::fileSuccesfullyDropped,
                     this, &MainWindow::fileUploaded);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileUploaded() {
    ui->statusbar->showMessage("File Succesfully Uploaded");
}

void MainWindow::on_pushButton_clicked() {
    Mp3Tag *tag = ui->frame->getTag();

    if (ui->title->text().isEmpty() == false)
        tag->setTitle(ui->title->text());
    if (ui->artist->text().isEmpty() == false)
        tag->setArtist(ui->artist->text());
    if (ui->album->text().isEmpty() == false)
        tag->setAlbum(ui->album->text());
    if (ui->year->text().isEmpty() == false)
        tag->setYear(ui->year->text());
    tag->showFields();
    ui->statusbar->showMessage("Tags was succesfully saved!");
}
