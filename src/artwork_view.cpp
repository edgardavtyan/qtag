#include <QMimeData>
#include <QDragEnterEvent>
#include <QBuffer>
#include "artwork_view.hpp"

ArtworkView::ArtworkView() {
    setFixedSize(150, 150);
    setScaledContents(true);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("border: 1px solid black;");
    setAcceptDrops(true);
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
    if (not file.endsWith(".jpg")) {
        return;
    }

    QPixmap pixmap(file);
    setPixmap(pixmap);
    QBuffer buffer(&m_artwork_data);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "JPEG", 90);
    buffer.close();
}

void ArtworkView::set_artwork(QByteArray data) {
    QPixmap pixmap;
    pixmap.loadFromData(data);
    setPixmap(pixmap);
    QBuffer buffer(&m_artwork_data);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "JPEG", 90);
    buffer.close();
}

QByteArray ArtworkView::get_artwork() {
    return m_artwork_data;
}
