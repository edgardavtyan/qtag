#pragma once

#include <QAbstractListModel>
#include "file_list_item.hpp"

class FileModel : public QAbstractListModel {
public:
    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void set_items(std::vector<FileListItem> items);
    FileListItem at(int row);
private:
    std::vector<FileListItem> m_items;
};
