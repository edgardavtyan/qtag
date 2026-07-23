#include <algorithm>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDir>
#include <QDirIterator>
#include "file_list.hpp"
#include "file_list_item.hpp"

FileList::FileList() {
    setAcceptDrops(true);
    setModel(&m_model);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    QObject::connect(selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
        std::vector<FileListItem> list;
        for (QModelIndex &idx : selectedIndexes()) {
            list.push_back(m_model.at(idx.row()));
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
    QStringList files;
    for (QUrl &url : e->mimeData()->urls()) {
        QFileInfo file(url.toLocalFile());
        if (file.isDir() and file.exists()) {
            QDirIterator dirit(QDir(url.toLocalFile()).path(), QStringList() << "*.mp3", QDir::Files,
                               QDirIterator::Subdirectories);
            while (dirit.hasNext()) {
                files.append(dirit.next());
            }
        }
        if (file.isFile() and file.exists() and file.suffix() == "mp3") {
            files.append(file.path());
        }
    }
    files.sort();

    std::vector<FileListItem> listitems;
    QString dirname;
    for (QString &file : files) {
        QString dir = file.section("/", -2, -2);
        if (dirname != dir) {
            dirname = dir;
            listitems.push_back(FileListItem(true, dirname));
        }
        listitems.push_back(FileListItem(false, file));
    }

    m_model.set_items(listitems);
}

std::vector<FileListItem> FileList::selected_items() {
    std::vector<FileListItem> list;
    for (QModelIndex &idx : selectedIndexes()) {
        list.push_back(m_model.at(idx.row()));
    }
    return list;
}
