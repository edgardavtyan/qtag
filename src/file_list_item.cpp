#include "file_list_item.hpp"

FileListItem::FileListItem(bool is_dir, QString text) {
    this->is_dir = is_dir;
    this->text = text;
}
