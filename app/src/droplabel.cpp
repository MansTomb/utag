#include "droplabel.h"
#include "QVBoxLayout"

DropLabel::DropLabel(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();

    text = new QLabel();
//    image = new QLabel();
    setLayout(layout);
    layout->addWidget(text, Qt::AlignCenter);
//    layout->addWidget(image, Qt::AlignCenter);
    text->setText("Drop File Here!");
}

void DropLabel::setText(QString str) {
//    QPixmap icon(":/images/images/music-icon.jpg");

    text->setText(str);
    text->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
//    image->setPixmap(icon.scaled(parentWidget()->width(), parentWidget()->height(), Qt::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
}

void DropLabel::fileDropped(QString &fname) {

}
