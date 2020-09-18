#include "droptablewidget.h"
#include "DirProcess.h"
#include <QDebug>

DropTableWidget::DropTableWidget(QWidget *parent) : QTableWidget(parent) {
    setAcceptDrops(true);
}

void DropTableWidget::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void DropTableWidget::dragMoveEvent(QDragMoveEvent *event) {
    event->accept();
}
void DropTableWidget::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}

void DropTableWidget::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        UpdateTable(urlList);
        event->acceptProposedAction();
    }
}

void DropTableWidget::UpdateTable(QList<QUrl> &urlList) {
    DirProcess processer;
    for (const auto &url : urlList) {
        auto filesInDir = processer.ProcessDirectory(url.path());
        for (const auto &file : filesInDir) {
            if (!files.contains(file.absoluteFilePath())) {
                insertRow(rowCount());
                setItem(rowCount() - 1, 0, new QTableWidgetItem(file.fileName()));
            }
            files.insert(file.absoluteFilePath());
        }
    }
}

void DropTableWidget::UpdateTable(QString directory) {
    DirProcess processer;

    for (const auto &file : processer.ProcessDirectory(directory)) {
        if (!files.contains(file.absoluteFilePath())) {
            insertRow(rowCount());
            setItem(rowCount() - 1, 0, new QTableWidgetItem(file.fileName()));
        }
        files.insert(file.absoluteFilePath());
    }
}
void DropTableWidget::commitData(QWidget *editor) {
    QAbstractItemView::commitData(editor);

    for (auto &item : selectedIndexes()) {
        model()->setData(item, currentItem()->data(Qt::EditRole), Qt::EditRole);
    }
}
void DropTableWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Delete) {
        auto selected = selectedItems();
        QList<int> rows;
        for (const auto &item : selected)
            rows.append(item->row());
        qSort(rows);
        rows.erase(std::unique(rows.begin(), rows.end()), rows.end());
        for (int i = rows.count() - 1; i >= 0; i--) {
            files.remove(itemAt(rows[i], 5)->text());
            if (i == 0)
                setEditTriggers(QAbstractItemView::NoEditTriggers);
            removeRow(rows[i]);
        }
        setEditTriggers(QAbstractItemView::DoubleClicked);
    }
    else
        QAbstractItemView::keyPressEvent(event);
}
