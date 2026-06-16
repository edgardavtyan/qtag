#include <QMimeData>
#include <QDragEnterEvent>
#include "artwork_view.hpp"

ArtworkView::ArtworkView() {
    setFixedSize(150, 150);
    setScaledContents(true);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("border: 1px solid black;");
}

void ArtworkView::dragEnterEvent(QDragEnterEvent *e) {
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void ArtworkView::dragMoveEvent(QDragMoveEvent *e) {
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void ArtworkView::dropEvent(QDropEvent *e) {
    QString file = e->mimeData()->urls()[0].toLocalFile();
}

void ArtworkView::set_artwork(QByteArray data) {
    QPixmap image;
    image.loadFromData(data);
    setPixmap(image);
}
