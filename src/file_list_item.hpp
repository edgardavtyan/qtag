#pragma once

#include <QString>

struct FileListItem {
    QString text;
    bool is_dir;

    FileListItem(bool is_dir, QString text);
};
