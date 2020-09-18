#pragma once

#include <QSet>

class DirProcess {
 public:
    QList<QFileInfo> ProcessDirectory(QString directory);
};
