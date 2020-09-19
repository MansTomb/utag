#pragma once

#include <QSet>

class DirProcess {
 public:
    QList<QFileInfo> ProcessDirectory(QString directory);
    QList<QFileInfo> ProcessDirectoryRecursively(QString directory);
 private:
    QDir getDir(const QUrl &directory) const;
};
