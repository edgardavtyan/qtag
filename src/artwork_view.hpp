#pragma once

#include <QLabel>

class ArtworkView : public QLabel {
    Q_OBJECT
public:
    ArtworkView();
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dragMoveEvent(QDragMoveEvent *e) override;
    void dropEvent(QDropEvent *e) override;
    void set_artwork(QByteArray data);
    QByteArray artwork();
    int artwork_width();
    int artwork_height();
signals:
    void on_drag_drop();
private:
    QByteArray m_artwork_data;
    int m_artwork_width;
    int m_artwork_height;
};
