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
    emit Notify("You dropped directories to table successfully!");
}

void DropTableWidget::UpdateTable(QList<QUrl> &urlList) {
    DirProcess processer;
    QList<QFileInfo> filesInDir;
    try {
        filesInDir = processer.ProcessDirectories(urlList);
    }
    catch (std::invalid_argument& e) {
        emit Notify(e.what());
        return;
    }
    for (const auto &file : filesInDir) {
        if (!files.contains(file.absoluteFilePath())) {
            insertRow(rowCount());
            setItem(rowCount() - 1, 0, new QTableWidgetItem(file.fileName()));
        }
        files.insert(file.absoluteFilePath());
    }
    emit Notify("Table was updated successfully!");
}

void DropTableWidget::UpdateTable(QString directory) {
    DirProcess processer;

    try {
        for (const auto &file : processer.ProcessDirectory(directory)) {
            if (!files.contains(file.absoluteFilePath()))
                CreateElement(file.fileName(), file.absoluteFilePath());
            files.insert(file.absoluteFilePath());
        }
    }
    catch (std::invalid_argument& e) {
        emit Notify(e.what());
        return;
    }
    emit Notify("Table was updated successfully!");
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
            files.remove(item(rows[i], 5)->text());
            removeRow(rows[i]);
        }
    }
    else
        QAbstractItemView::keyPressEvent(event);
}

void DropTableWidget::ClearTable() {
    files.clear();
    model()->removeRows(0, model()->rowCount());
    emit Notify("Table was cleared successfully!");
}

void DropTableWidget::CreateElement(QString fname, QString absPath) {
    insertRow(rowCount());
    setItem(rowCount() - 1, 0, new QTableWidgetItem(fname));
    setItem(rowCount() - 1, 5, new QTableWidgetItem(absPath));
}

