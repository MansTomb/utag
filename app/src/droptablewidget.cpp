#include "droptablewidget.h"
#include "DirProcess.h"
#include "dropdialog.h"
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
    if (mimeData->hasUrls() && OpenDialog()) {
        QList<QUrl> urlList = mimeData->urls();
        if (!Append)
            ClearTable();
        UpdateTable(urlList);
        event->acceptProposedAction();
    }
}

void DropTableWidget::UpdateTable(QList<QUrl> &urlList) {
    for (const auto &url : urlList)
        UpdateTable(url.path());
}

void DropTableWidget::UpdateTable(QString directory) {
    DirProcess processer;
    try {
        for (const auto &file : processer.Process(directory, AcceptRecursive)) {
            if (findItems(file.absoluteFilePath(), Qt::MatchExactly).isEmpty()) {
                Tagger tagger;
                auto audioFile = tagger.ReadFile(file.absoluteFilePath());
                if (Filter(audioFile))
                    CreateElement(audioFile);
            }
        }
    }
    catch (std::invalid_argument& e) {
        emit Notify(e.what());
        return;
    }
    emit Notify(directory.append(" was added to table successfully!").prepend("Files from"));
}
void DropTableWidget::commitData(QWidget *editor) {
    QAbstractItemView::commitData(editor);

    for (auto &item : selectedIndexes())
        model()->setData(item, currentItem()->data(Qt::EditRole), Qt::EditRole);
}
void DropTableWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Delete) {
        QList<int> rows = getRowsToDelete();
        for (int i = rows.count() - 1; i >= 0; i--)
            removeRow(rows[i]);
    }
    else
        QAbstractItemView::keyPressEvent(event);
}
QList<int> DropTableWidget::getRowsToDelete() const {
    auto selected = selectedItems();
    QList<int> rows;

    for (const auto &item : selected)
        rows.append(item->row());
    qSort(rows);
    rows.erase(std::unique(rows.begin(), rows.end()), rows.end());
    return rows;
}

void DropTableWidget::ClearTable() {
    model()->removeRows(0, model()->rowCount());
    emit Notify("Table was cleared successfully!");
}

void DropTableWidget::CreateElement(AudioFile file) {
    insertRow(rowCount());
    setItem(rowCount() - 1, 0, new QTableWidgetItem(file.title));
    setItem(rowCount() - 1, 1, new QTableWidgetItem(file.artist));
    setItem(rowCount() - 1, 2, new QTableWidgetItem(file.album));
    setItem(rowCount() - 1, 3, new QTableWidgetItem(file.genre));
    setItem(rowCount() - 1, 4, new QTableWidgetItem(file.year));
    QTableWidgetItem *item = new QTableWidgetItem(file.absPath);
    item->setFlags(item->flags() ^ Qt::ItemIsEditable ^ Qt::ItemIsSelectable);
    setItem(rowCount() - 1, 5, item);
}

void DropTableWidget::ProcessOptions(QString tag, bool recursive, bool append) {
    this->tag = tag.split(' ');
    AcceptRecursive = recursive;
    Append = append;
}

int DropTableWidget::OpenDialog() {
    DropDialog *dialog = new DropDialog();
    QObject::connect(dialog, &DropDialog::ReturnValues,
                     this, &DropTableWidget::ProcessOptions);
    return dialog->exec();
}

bool DropTableWidget::Filter(AudioFile &file) {
    if (tag.isEmpty())
        return true;
    if (tag[1].isEmpty())
        return true;
    if (tag[0] == "Title")
        return tag[1] == file.title;
    else if (tag[0] == "Artist")
        return tag[1] == file.artist;
    else if (tag[0] == "Album")
        return tag[1] == file.album;
    else if (tag[0] == "Genre")
        return tag[1] == file.genre;
    else if (tag[0] == "Year")
        return tag[1] == file.year;
    return false;
}
