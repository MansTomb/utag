#include "droptablewidget.h"
#include "DirProcess.h"
#include "dropdialog.h"
#include <QDebug>

DropTableWidget::DropTableWidget(QWidget *parent) : QTableWidget(parent) {
    setAcceptDrops(true);
}

void DropTableWidget::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls() && OpenDialog()) {
        QList<QUrl> urlList = mimeData->urls();
        m_Append ? static_cast<void>(nullptr) : ClearTable();
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
        for (const auto &file : processer.Process(directory, m_AcceptRecursive)) {
            if (findItems(file.absoluteFilePath(), Qt::MatchExactly).isEmpty()) {
                if (!file.isReadable() || !file.isWritable()) {
                    emit Notify(file.fileName().append(" not readable or writable!"));
                    continue;
                }
                Tagger tagger;
                auto audioFile = tagger.ReadFile(file.absoluteFilePath());
                if (Filter(audioFile))
                    CreateElement(audioFile);
            }
        }
    }
    catch (std::invalid_argument &e) {
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
    } else
        QAbstractItemView::keyPressEvent(event);
}

QList<int> DropTableWidget::getRowsToDelete() const {
    auto selected = selectedItems();
    QList<int> rows;

    for (const auto &item : selected)
        rows.append(item->row());
    std::sort(rows.begin(), rows.end());
    rows.erase(std::unique(rows.begin(), rows.end()), rows.end());
    return rows;
}

void DropTableWidget::ClearTable() {
    model()->removeRows(0, model()->rowCount());
    emit Notify("Table was cleared successfully!");
}

void DropTableWidget::CreateElement(AudioFile file) {
    auto *year = new QTableWidgetItem();
    auto *absPath = new QTableWidgetItem(file.absPath);

    if (file.year != 0)
        year->setData(Qt::EditRole, file.year);
    absPath->setFlags(absPath->flags() ^ Qt::ItemIsEditable ^ Qt::ItemIsSelectable);
    insertRow(rowCount());
    setItem(rowCount() - 1, 0, new QTableWidgetItem(file.title));
    setItem(rowCount() - 1, 1, new QTableWidgetItem(file.artist));
    setItem(rowCount() - 1, 2, new QTableWidgetItem(file.album));
    setItem(rowCount() - 1, 3, new QTableWidgetItem(file.genre));
    setItem(rowCount() - 1, 4, year);
    setItem(rowCount() - 1, 5, absPath);
}

void DropTableWidget::ProcessOptions(QString tag, bool recursive, bool append) {
    m_tag = tag.split(' ');
    m_AcceptRecursive = recursive;
    m_Append = append;
}

int DropTableWidget::OpenDialog() {
    DropDialog *dialog = new DropDialog();
    QObject::connect(dialog, &DropDialog::ReturnValues,
                     this, &DropTableWidget::ProcessOptions);
    return dialog->exec();
}

bool DropTableWidget::Filter(AudioFile &file) {
    if (file.isWrong())
        return false;
    if (m_tag.isEmpty())
        return true;
    if (m_tag[1].isEmpty())
        return true;
    if (m_tag[0] == "Title")
        return m_tag[1] == file.title;
    else if (m_tag[0] == "Artist")
        return m_tag[1] == file.artist;
    else if (m_tag[0] == "Album")
        return m_tag[1] == file.album;
    else if (m_tag[0] == "Genre")
        return m_tag[1] == file.genre;
    else if (m_tag[0] == "Year")
        return m_tag[1].toUInt() == file.year;
    return false;
}
