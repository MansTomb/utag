#include "filedropframe.h"
#include "droplabel.h"
#include "mp3tag.h"

#include "QDebug"
#include "QDragEnterEvent"
#include "QDropEvent"
#include "QMimeData"
#include "QLabel"
#include "QLineEdit"
#include "QStatusBar"

FileDropFrame::FileDropFrame(QWidget *parent) : QFrame(parent)
{
    setAcceptDrops(true);
}

void FileDropFrame::dropEvent(QDropEvent *event) {
    foreach (const QUrl &url, event->mimeData()->urls()) {
        QString fileName = url.toLocalFile();

        tags = new Mp3Tag(fileName);
        setLines();
        emit fileSuccesfullyDropped();
    }
}

void FileDropFrame::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

Mp3Tag *FileDropFrame::getTag() {
    return tags;
}

void FileDropFrame::setLines() {
    if (tags) {
        findChild<DropLabel*>("drop_label")->setText(tags->getTitle());
        parent()->findChild<QLineEdit*>("title")->setText(tags->getTitle());
        parent()->findChild<QLineEdit*>("artist")->setText(tags->getArtist());
        parent()->findChild<QLineEdit*>("album")->setText(tags->getAlbum());
        parent()->findChild<QLineEdit*>("year")->setText(tags->getYear());
    }
    else
        qDebug() << "Mp3Tags class not exist!";
}
