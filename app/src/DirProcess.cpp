#include <QtCore/QDir>
#include <QtGui/QDropEvent>
#include <QDebug>
#include <iostream>
#include "DirProcess.h"

QFileInfo DirProcess::getFile(const QUrl &file) const {
    auto path = file.url();
    return QFileInfo(path);
}

QDir DirProcess::getDir(const QUrl &directory) const {
    auto path = directory.url();
    QDir dir(path);
    if (!dir.exists() || !dir.isReadable())
        throw std::invalid_argument(dir.path().toStdString() + " not exist or not readable!");
    return dir;
}

QList<QFileInfo> DirProcess::ProcessFile(const QString &directory) const {
    auto file = getFile(directory);
    if (file.exists() && file.isFile() && file.fileName().contains(QRegExp(FILEFILTER)))
        return QList<QFileInfo>() += file;
    return QList<QFileInfo>();
}

QList<QFileInfo> DirProcess::ProcessDirectory(const QString &directory) {
    QDir dir = getDir(directory);
    QList<QFileInfo> list = dir.entryInfoList();

    list.erase(std::remove_if(list.begin(), list.end(), [](QFileInfo &item) {
        return item.isDir() || !item.fileName().contains(QRegExp(FILEFILTER));
    }), list.end());
    for (const auto &item : list) {
        std::cout << "::" << item.absolutePath().toStdString() << std::endl;
    }
    return list;
}

QList<QFileInfo> DirProcess::ProcessDirectoryRecursively(const QString &directory) {
    QDir dir = getDir(directory);
    QList<QFileInfo> list = dir.entryInfoList();
    QList<QFileInfo> listOfDirs;

    std::copy_if(list.begin(), list.end(), std::back_inserter(listOfDirs), [](QFileInfo &i) {
        return i.fileName() != "." && i.fileName() != ".." && i.exists() && i.isDir() && i.isReadable();
    });
    list.erase(std::remove_if(list.begin(), list.end(), [](QFileInfo &item) {
        return item.isDir() || !item.fileName().contains(QRegExp(FILEFILTER));
    }), list.end());
    for (const auto &item : listOfDirs)
        list += ProcessDirectoryRecursively(item.absoluteFilePath());
    for (const auto &item : list) {
        std::cout << item.absolutePath().toStdString() << std::endl;
    }
    return list;
}

QList<QFileInfo> DirProcess::Process(const QString &directory, bool Recursive) {
    if (!ProcessFile(directory).empty())
        return ProcessFile(directory);
    if (Recursive)
        return ProcessDirectoryRecursively(directory);
    return ProcessDirectory(directory);
}
