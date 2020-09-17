#ifndef FILEDROPFRAME_H
#define FILEDROPFRAME_H

#include "QFrame"
#include "mp3tag.h"

class FileDropFrame : public QFrame
{
    Q_OBJECT
public:
    explicit FileDropFrame(QWidget *parent = Q_NULLPTR);
    void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    Mp3Tag *getTag();
    void setLines();

signals:
    void fileSuccesfullyDropped();

private:
    Mp3Tag *tags;
};

#endif // FILEDROPFRAME_H
