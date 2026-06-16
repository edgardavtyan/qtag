#include "file_list.hpp"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDir>
#include <QDirIterator>

FileList::FileList() {
    setAcceptDrops(true);
    setModel(&m_model);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    QObject::connect(selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
        QStringList list;
        for (QModelIndex &idx : selectedIndexes()) {
            list.append(m_model.at(idx.row()));
        }
        emit selection_changed(list);
    });
}

void FileList::dragEnterEvent(QDragEnterEvent *e) {
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void FileList::dragMoveEvent(QDragMoveEvent *e) {
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void FileList::dropEvent(QDropEvent *e) {
    QList<QString> files;
    for (QUrl &url : e->mimeData()->urls()) {
        QString file = url.toLocalFile();
        if (QDir(file).exists()) {
            QDirIterator dirit(QDir(file).path(), QStringList() << "*.mp3", QDir::Files,
                               QDirIterator::Subdirectories);
            while (dirit.hasNext()) {
                files.append(dirit.next());
            }
        }
    }
    m_model.set_items(files);
}

QStringList FileList::selected_items() {
    QStringList list;
    for (QModelIndex &idx : selectedIndexes()) {
        list.append(m_model.at(idx.row()));
    }
    return list;
}
