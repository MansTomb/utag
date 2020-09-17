#ifndef MP3TAG_H
#define MP3TAG_H

#include "QString"
#include "QFile"

class Mp3Tag
{
public:
    Mp3Tag(QString fname);
    ~Mp3Tag();
    QString getArtist();
    QString getTitle();
    QString getAlbum();
    QString getYear();
    void setArtist(QString str);
    void setTitle(QString str);
    void setAlbum(QString str);
    void setYear(QString str);
    void showFields();

private:
    QFile *file;
    QString filename;
    QString artist;
    QString title;
    QString album;
    QString year;
    QString comment;
    void read();
};

#endif // MP3TAG_H
