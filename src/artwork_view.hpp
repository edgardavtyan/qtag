#pragma once

#include <QLabel>

class ArtworkView : public QLabel {
public:
    ArtworkView();
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dragMoveEvent(QDragMoveEvent *e) override;
    void dropEvent(QDropEvent *e) override;
    void set_artwork(QByteArray data);
};
