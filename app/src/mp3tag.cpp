#include "mp3tag.h"
#include "fileutils.h"
#include "QDebug"

Mp3Tag::Mp3Tag(QString fname)
{
    file = new QFile(fname);
    file->open(QIODevice::ReadWrite | QIODevice::Text);
    filename = fname;

    if (file) {
//        if (CheckHeader(file, file->size() - 128) == "tag") {
            read();
//        }
//        else
//            qDebug() << "File not tagged!";
    }
}

Mp3Tag::~Mp3Tag() {
    file->close();
}

QString Mp3Tag::getArtist() {
    return artist;
}

QString Mp3Tag::getTitle() {
    return title;
}

QString Mp3Tag::getAlbum() {
    return album;
}

QString Mp3Tag::getYear() {
    return year;
}

void Mp3Tag::setArtist(QString str) {
    artist = str;
    file->seek(file->size() - 95);
    file->write(str.toStdString().c_str(), 30);
    qDebug() << artist << " set as The Artist";
}

void Mp3Tag::setTitle(QString str) {
    title = str;
    file->seek(file->size() - 125);
    file->write(str.toStdString().c_str(), 30);
    qDebug() << title << " set as Title";
}

void Mp3Tag::setAlbum(QString str) {
    album = str;
    file->seek(file->size() - 65);
    file->write(str.toStdString().c_str(), 30);
    qDebug() << album << " set as Album";
}

void Mp3Tag::setYear(QString str) {
    year = str;
    file->seek(file->size() - 35);
    file->write(str.toStdString().c_str(), 4);
    qDebug() << year << " set as Year";
}


void Mp3Tag::read() {
    int readloc = file->size() - 125;

    title = ReadThirty(file, readloc);
    readloc+=30;
    artist = ReadThirty(file, readloc);
    readloc+=30;
    album = ReadThirty(file, readloc);
    readloc+=30;
    year = Year(file, readloc);
}

void Mp3Tag::showFields() {
    qDebug() << "Title: " << title << "\n" << "Artist: " << artist << "\n"<< "Album: " << album << "\n" << "Year: " << year << "\n";
}
