#pragma once

#include <QListView>
#include "file_model.hpp"

class FileList : public QListView {
    Q_OBJECT
public:
    FileList();
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dragMoveEvent(QDragMoveEvent *e) override;
    void dropEvent(QDropEvent *e) override;
signals:
    void selection_changed(QStringList list);
private:
    FileModel m_model;
};
