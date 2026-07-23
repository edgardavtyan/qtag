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

    set_artwork_from_pixmap(QPixmap(file));
    emit on_drag_drop();
}

void ArtworkView::set_artwork(QByteArray data) {
    QPixmap pixmap;
    pixmap.loadFromData(data);
    set_artwork_from_pixmap(pixmap);
}

QByteArray ArtworkView::artwork() {
    return m_artwork_data;
}

int ArtworkView::artwork_width() {
    return m_artwork_width;
}

int ArtworkView::artwork_height() {
    return m_artwork_height;
}

void ArtworkView::set_artwork_from_pixmap(const QPixmap &pixmap) {
    setPixmap(pixmap);
    m_artwork_width = pixmap.width();
    m_artwork_height = pixmap.height();
    QBuffer buffer(&m_artwork_data);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "JPEG", 90);
    buffer.close();
}
