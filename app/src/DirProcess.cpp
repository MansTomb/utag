#include <QtCore/QDir>
#include <QDebug>
#include "DirProcess.h"

QList<QFileInfo> DirProcess::ProcessDirectory(QString directory) {
    if (directory.at(0) == '/')
        directory.remove(0, 1);
    QDir dir(directory);
    auto list = dir.entryInfoList();

    list.erase(std::remove_if(list.begin(), list.end(), [](QFileInfo &item) {
        return item.isDir() || !item.fileName().contains(QRegExp(".mp3"));
    }), list.end());
    return list;
}
