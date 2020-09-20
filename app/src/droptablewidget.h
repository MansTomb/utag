#pragma once

#include <QWidget>
#include <QtGui/QDrag>
#include <QtGui/QDropEvent>
#include <QtCore/QMimeData>
#include <QtWidgets/QTableWidget>
#include <QtCore/QFileInfo>
#include "tagger.h"

class DropTableWidget : public QTableWidget {
    Q_OBJECT

 public:
    explicit DropTableWidget(QWidget *parent = Q_NULLPTR);
    void UpdateTable(QString directory);
 protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void commitData(QWidget *editor) override;

public slots:
    void ClearTable();
    void ProcessOptions(QString tag, bool recursive, bool append);
signals:
    void Notify(QString message);
 private:
    bool AcceptRecursive = {false};
    bool Append = {false};
    QStringList tag;

    void UpdateTable(QList<QUrl> &urlList);
    void CreateElement(AudioFile file);
    QList<int> getRowsToDelete() const;
    int OpenDialog();
    bool Filter(AudioFile& file);
};
