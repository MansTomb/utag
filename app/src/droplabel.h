#ifndef DROPLABEL_H
#define DROPLABEL_H

#include <QWidget>
#include "QLabel"

class DropLabel : public QWidget
{
    Q_OBJECT
public:
    explicit DropLabel(QWidget *parent = nullptr);
    void setText(QString str);
    void fileDropped(QString &fname);

private:
    QLabel *image;
    QLabel *text;
signals:

};

#endif // DROPLABEL_H
