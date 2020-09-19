#pragma once

#include <QWidget>
#include <QtGui/QDrag>
#include <QtGui/QDropEvent>
#include <QtCore/QMimeData>
#include <QtWidgets/QTableWidget>
#include <QtCore/QFileInfo>

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
signals:
    void Notify(QString message);
 private:
    QSet<QString> files;
    void UpdateTable(QList<QUrl> &urlList);
    void CreateElement(QString fname, QString absPath);
};
