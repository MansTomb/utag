#ifndef DROPDIALOG_H
#define DROPDIALOG_H

#include <QDialog>

namespace Ui {
class DropDialog;
}

class DropDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DropDialog(QWidget *parent = nullptr);
    ~DropDialog();
    void accept() override;

 signals:
    void ReturnValues(QString tag, bool recursive, bool append);

private:
    Ui::DropDialog *ui;
};

#endif // DROPDIALOG_H
