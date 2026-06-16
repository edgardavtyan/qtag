#pragma once

#include <QListView>
#include "file_model.hpp"

class FileList : public QListView {
public:
    FileList();
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dragMoveEvent(QDragMoveEvent *e) override;
    void dropEvent(QDropEvent *e) override;
private:
    FileModel m_model;
    bool is_file_supported(QString file);
};
