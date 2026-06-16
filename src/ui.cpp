#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include "ui.hpp"

UI::UI(int& argc, char**& argv): m_app(argc, argv) {
    QHBoxLayout *toolbar_box = new QHBoxLayout();

    QVBoxLayout *tag_box = new QVBoxLayout();
    tag_box->setAlignment(Qt::AlignTop);
    tag_box->addWidget(new QLabel("Title:"));
    tag_box->addWidget(&m_edit_title);
    tag_box->addWidget(new QLabel("Artist:"));
    tag_box->addWidget(&m_edit_artist);
    tag_box->addWidget(new QLabel("Album:"));
    tag_box->addWidget(&m_edit_album);
    tag_box->addWidget(new QLabel("Date:"));
    tag_box->addWidget(&m_edit_date);

    QHBoxLayout *second_box = new QHBoxLayout();
    second_box->addWidget(&m_file_list);
    second_box->addLayout(tag_box);

    QVBoxLayout *main_box = new QVBoxLayout(&m_root);
    main_box->addLayout(toolbar_box);
    main_box->addLayout(second_box);

    connect(&m_file_list, &FileList::selection_changed, [&](QStringList list) {
        emit selection_changed(list);
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

void UI::set_date(QString date) {
    m_edit_date.setPlaceholderText("");
    m_edit_date.setText(date);
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

void UI::set_different_dates() {
    m_edit_date.setPlaceholderText("Different values");
    m_edit_date.setText("");
}
