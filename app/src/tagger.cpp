#include "tagger.h"

#include <QtCore/QFileInfo>

Tagger::Tagger(QObject *parent) : QObject(parent) {

}

AudioFile Tagger::ReadFile(const QString &absPath) {
    QFileInfo info(absPath);

    if (info.exists() && info.isReadable() && info.isWritable())
        return {"Song","Boy", "Pervii", "Rock", "2001", info.absoluteFilePath()};
    emit Notify(info.absoluteFilePath().append(" is not exist or has bad permissions!"));
    return {"","", "", "", "", "WRONGFILE"};
}
void Tagger::UpdateTagsInFile(AudioFile file) {
    QFileInfo info(file.absPath);

    file.genre = "Updated";
}
