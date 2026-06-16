#include "file_list.hpp"
#include <filesystem>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDir>
#include <QDirIterator>

FileList::FileList() {
    setAcceptDrops(true);
    setModel(&m_model);
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
            QDirIterator dirit(QDir(file).path(), QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);
            while (dirit.hasNext()) {
                files.append(dirit.next());
            }
        }
    }
    m_model.set_items(files);
}

bool FileList::is_file_supported(QString file) {
    return file.endsWith("*.mp3");
}
