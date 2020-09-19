#pragma once

#include <QSet>

class DirProcess {
 public:
    QList<QFileInfo> ProcessDirectory(QString directory);
    QList<QFileInfo> ProcessDirectories(QList<QUrl>& directories);
};
