#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString& initialFolder = "", QWidget *parent = nullptr);
    ~MainWindow();
 public slots:
    void ChangeTheme(bool toggler);
private slots:
    void on_ApplyButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
