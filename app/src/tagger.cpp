#include "tagger.h"

#include <QtCore/QFileInfo>
#include <QDebug>
#include <taglib/fileref.h>
#include <taglib/tag.h>

Tagger::Tagger(QObject *parent) : QObject(parent) {

}

AudioFile Tagger::ReadFile(const QString &absPath) {
    QFileInfo info(absPath);
    TagLib::FileRef f(absPath.toStdString().c_str());

    if (!f.isNull() && info.exists() && info.isReadable() && info.isWritable())
        return {f.tag()->title().toCString(true),
                f.tag()->artist().toCString(true),
                f.tag()->album().toCString(true),
                f.tag()->genre().toCString(true),
                f.tag()->year(),
                info.absoluteFilePath()
        };
    emit Notify(info.absoluteFilePath().append(" is not exist or has bad permissions!"));
    return {"","", "", "", 0, "WRONGFILE"};
}
void Tagger::UpdateTagsInFile(AudioFile file) {
    QFileInfo info(file.absPath);
    TagLib::FileRef f(file.absPath.toStdString().c_str());

    if (!f.isNull()) {
        f.tag()->setTitle(file.title.toStdWString());
        f.tag()->setArtist(file.artist.toStdWString());
        f.tag()->setAlbum(file.album.toStdWString());
        f.tag()->setGenre(file.genre.toStdWString());
        if (file.year != 0)
            f.tag()->setYear(file.year);
        f.save();
    }
    else
        emit Notify("Taglib FileRef is NULL!");
}
