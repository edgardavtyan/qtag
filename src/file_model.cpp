#include "file_model.hpp"

int FileModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_items.size();
}

QVariant FileModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        FileListItem item = m_items[index.row()];
        if (item.is_dir) {
            return item.text;
        }
        else {
            return "    " + item.text.section("/", -1, -1);
        }
    }
    return {};
}

Qt::ItemFlags FileModel::flags(const QModelIndex &index) const {
    FileListItem item = m_items[index.row()];
    if (item.is_dir) {
        return Qt::NoItemFlags;
    }
    else {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
}

void FileModel::set_items(std::vector<FileListItem> items) {
    m_items = items;
    dataChanged(createIndex(0, 0), createIndex(0, 0));
}

FileListItem FileModel::at(int row) {
    return m_items[row];
}
