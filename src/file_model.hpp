#pragma once

#include <QAbstractListModel>

class FileModel : public QAbstractListModel {
public:
    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void set_items(QStringList items);
    QString at(int row);
private:
    QStringList m_items;
};
