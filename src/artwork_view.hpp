#pragma once

#include <QLabel>

class ArtworkView : public QLabel {
public:
    ArtworkView();
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dragMoveEvent(QDragMoveEvent *e) override;
    void dropEvent(QDropEvent *e) override;
    void set_artwork(QByteArray data);
    QByteArray get_artwork();
    int artwork_width();
    int artwork_height();
private:
    QByteArray m_artwork_data;
    int m_artwork_width;
    int m_artwork_height;
};
