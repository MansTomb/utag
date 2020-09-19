#include <QtCore/QDir>
#include <QtCore/QMimeData>
#include <QtGui/QDropEvent>
#include <QDebug>
#include "DirProcess.h"

QList<QFileInfo> DirProcess::ProcessDirectory(QString directory) {
    if (directory.at(0) == '/')
        directory.remove(0, 1);
    QDir dir(directory);
    if (!dir.exists() || !dir.isReadable())
        throw std::invalid_argument(directory.toStdString() + " not exist or not readable!");

    auto list = dir.entryInfoList();

    list.erase(std::remove_if(list.begin(), list.end(), [](QFileInfo &item) {
        return item.isDir() || !item.fileName().contains(QRegExp(".mp3"));
    }), list.end());
    return list;
}

QList<QFileInfo> DirProcess::ProcessDirectories(QList<QUrl> &directories) {
    QList<QFileInfo> list;
    for (const auto &directory : directories) {
        QDir dir(directory.path());
        if (!dir.exists() || !dir.isReadable())
            throw std::invalid_argument(directory.path().toStdString() + " not exist or not readable!");
    }
    for (const auto &directory : directories) {
        if (directory.path().at(0) == '/')
            directory.path().remove(0, 1);
        QDir dir(directory.path());
        list += dir.entryInfoList();
    }
    list.erase(std::remove_if(list.begin(), list.end(), [](QFileInfo &item) {
        return item.isDir() || !item.fileName().contains(QRegExp(".mp3"));
    }), list.end());
    return list;
}
