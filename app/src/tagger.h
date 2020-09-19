#ifndef TAGGER_H
#define TAGGER_H

#include <QObject>

struct AudioFile {
    QString title;
    QString artist;
    QString album;
    QString genre;
    QString year;
    const QString absPath;

    bool isWrong() {
        return absPath == "WRONGFILE";
    }
};

class Tagger : public QObject
{
    Q_OBJECT
public:
    explicit Tagger(QObject *parent = nullptr);
    AudioFile ReadFile(const QString& absPath);
    void UpdateTagsInFile(AudioFile file);
signals:
    void Notify(QString message);
};

#endif // TAGGER_H
