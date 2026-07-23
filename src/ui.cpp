#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <sstream>
#include "ui.hpp"

UI::UI(int& argc, char**& argv): m_app(argc, argv) {
    QHBoxLayout *toolbar_box = new QHBoxLayout();
    toolbar_box->setAlignment(Qt::AlignLeft);
    QPushButton *btn_save = new QPushButton("Save");
    connect(btn_save, &QPushButton::clicked, this, &UI::btn_save_clicked);
    toolbar_box->addWidget(btn_save);

    QVBoxLayout *tag_box = new QVBoxLayout();
    tag_box->setAlignment(Qt::AlignTop);
    tag_box->addLayout(toolbar_box);

    tag_box->addWidget(new QLabel("Title:"));
    tag_box->addWidget(&m_edit_title);
    tag_box->addWidget(new QLabel("Artist:"));
    tag_box->addWidget(&m_edit_artist);
    tag_box->addWidget(new QLabel("Album:"));
    tag_box->addWidget(&m_edit_album);
    tag_box->addWidget(new QLabel("Genre:"));
    tag_box->addWidget(&m_edit_genre);

    QHBoxLayout *year_track_box = new QHBoxLayout();

    QVBoxLayout *year_box = new QVBoxLayout();
    year_box->addWidget(new QLabel("Date:"));
    year_box->addWidget(&m_edit_year);
    year_track_box->addLayout(year_box);

    QVBoxLayout *track_box = new QVBoxLayout();
    track_box->addWidget(new QLabel("Track:"));
    track_box->addWidget(&m_edit_track);
    year_track_box->addLayout(track_box);

    tag_box->addLayout(year_track_box);

    tag_box->addSpacing(10);
    tag_box->addWidget(new QLabel("Artwork"));
    tag_box->addWidget(&m_artwork);
    tag_box->addWidget(&m_artwork_info);

    QHBoxLayout *main_box = new QHBoxLayout(&m_root);
    main_box->addWidget(&m_file_list);
    main_box->addLayout(tag_box);

    connect(&m_file_list, &FileList::selection_changed, [&](QStringList list) {
        emit selection_changed(list);
    });

    connect(&m_artwork, &ArtworkView::on_drag_drop, [&]() {
        std::stringstream ss;
        ss << m_artwork.artwork_width() << "x" << m_artwork.artwork_height();
        m_artwork_info.setText(QString::fromStdString(ss.str()));
    });
}

void UI::exec() {
    m_root.resize(600, 600);
    m_root.show();
    m_app.exec();
}

void UI::set_title(QString title) {
    m_edit_title.setPlaceholderText("");
    m_edit_title.setText(title);
}

void UI::set_artist(QString artist) {
    m_edit_artist.setPlaceholderText("");
    m_edit_artist.setText(artist);
}

void UI::set_album(QString album) {
    m_edit_album.setPlaceholderText("");
    m_edit_album.setText(album);
}

void UI::set_year(QString date) {
    m_edit_year.setPlaceholderText("");
    m_edit_year.setText(date);
}

void UI::set_track(QString track) {
    m_edit_track.setPlaceholderText("");
    m_edit_track.setText(track);
}

void UI::set_genre(QString genre) {
    m_edit_genre.setPlaceholderText("");
    m_edit_genre.setText(genre);
}

void UI::set_different_titles() {
    m_edit_title.setPlaceholderText("Different values");
    m_edit_title.setText("");
}

void UI::set_different_artists() {
    m_edit_artist.setPlaceholderText("Different values");
    m_edit_artist.setText("");
}

void UI::set_different_albums() {
    m_edit_album.setPlaceholderText("Different values");
    m_edit_album.setText("");
}

void UI::set_different_years() {
    m_edit_year.setPlaceholderText("Different values");
    m_edit_year.setText("");
}

void UI::set_different_tracks() {
    m_edit_track.setPlaceholderText("Different values");
    m_edit_track.setText("");
}

void UI::set_different_genres() {
    m_edit_genre.setPlaceholderText("Different values");
    m_edit_genre.setText("");
}

void UI::set_different_artwork() {
    m_artwork.clear();
    m_artwork.setText("Artwork varies");
}

QString UI::get_title() {
    return m_edit_title.text();
}

QString UI::get_artist() {
    return m_edit_artist.text();
}

QString UI::get_album() {
    return m_edit_album.text();
}

QString UI::get_year() {
    return m_edit_year.text();
}

QString UI::get_track() {
    return m_edit_track.text();
}

QString UI::get_genre() {
    return m_edit_genre.text();
}

void UI::set_artwork(QByteArray data) {
    m_artwork.set_artwork(data);
    std::stringstream ss;
    ss << m_artwork.artwork_width() << "x" << m_artwork.artwork_height();
    m_artwork_info.setText(QString::fromStdString(ss.str()));
}

void UI::clear_artwork() {
    m_artwork.clear();
    m_artwork_info.clear();
}

QByteArray UI::get_artwork() {
    return m_artwork.artwork();
}

QStringList UI::selected_files() {
    return m_file_list.selected_items();
}
