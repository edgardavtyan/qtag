#include "file_model.hpp"


int FileModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_items.size();
}

QVariant FileModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return m_items[index.row()].section("/", -1, -1);
    }
    return {};
}

void FileModel::set_items(QStringList items) {
    m_items = items;
    dataChanged(createIndex(0, 0), createIndex(0, 0));
}

QString FileModel::at(int row) {
    return m_items[row];
}
