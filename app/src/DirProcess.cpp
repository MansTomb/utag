#include <QtCore/QDir>
#include <QtCore/QMimeData>
#include <QtGui/QDropEvent>
#include <QDebug>
#include "DirProcess.h"

QFileInfo DirProcess::getFile(const QUrl &file) const {
    auto path = file.url();
    if (path.at(0) == '/')
        path.remove(0, 1);
    return QFileInfo(path);
}

QDir DirProcess::getDir(const QUrl &directory) const {
    auto path = directory.url();
    if (path.at(0) == '/')
        path.remove(0, 1);
    if (path.at(path.size() - 1) != '/')
        path += "/";
    QDir dir(path);
    if (!dir.exists() || !dir.isReadable())
        throw std::invalid_argument(dir.path().toStdString() + " not exist or not readable!");
    return dir;
}

QList<QFileInfo> DirProcess::ProcessFile(const QString &directory) const {
    auto file = getFile(directory);
    if (file.exists() && file.isFile() && file.isReadable() && file.isWritable())
        return QList<QFileInfo>() += file;
    return QList<QFileInfo>();
}

QList<QFileInfo> DirProcess::ProcessDirectory(const QString &directory) {
    QDir dir = getDir(directory);
    QList<QFileInfo> list = dir.entryInfoList();

    list.erase(std::remove_if(list.begin(), list.end(), [](QFileInfo &item) {
        return item.isDir() || !item.fileName().contains(QRegExp(R"(\.mp3$|\.flac$|\.wav$|\.ogg$)"));
    }), list.end());
    return list;
}

QList<QFileInfo> DirProcess::ProcessDirectoryRecursively(const QString &directory) {
    QDir dir = getDir(directory);
    QList<QFileInfo> list = dir.entryInfoList();
    QList<QFileInfo> listOfDirs;

    std::copy_if(list.begin(), list.end(), std::back_inserter(listOfDirs), [](QFileInfo& i) {
        return i.fileName() != "." && i.fileName() != ".." && i.exists() && i.isDir() && i.isReadable();
    });
    list.erase(std::remove_if(list.begin(), list.end(), [](QFileInfo &item) {
        return item.isDir() || !item.fileName().contains(QRegExp(R"(\.mp3$|\.flac$|\.wav$|\.ogg$)"));
    }), list.end());
    for (const auto &item : listOfDirs)
        list += ProcessDirectoryRecursively(item.absoluteFilePath());
    return list;
}

QList<QFileInfo> DirProcess::Process(const QString &directory, bool Recursive) {
    if (!ProcessFile(directory).empty())
        return ProcessFile(directory);
    if (Recursive)
        return ProcessDirectoryRecursively(directory);
    return ProcessDirectory(directory);
}
