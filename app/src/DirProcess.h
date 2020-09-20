#pragma once

#include <QSet>

class DirProcess {
 public:
    QList<QFileInfo> Process(const QString& directory, bool Recursive);
 private:
    QDir getDir(const QUrl &directory) const;
    QFileInfo getFile(const QUrl &file) const;
    QList<QFileInfo> ProcessFile(const QString &directory) const;
    QList<QFileInfo> ProcessDirectory(const QString &directory);
    QList<QFileInfo> ProcessDirectoryRecursively(const QString &directory);
};
