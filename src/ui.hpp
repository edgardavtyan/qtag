#pragma once

#include <QApplication>
#include <QWidget>
#include <QListView>
#include <QLineEdit>
#include "file_list.hpp"
#include "artwork_view.hpp"

class UI : public QObject {
    Q_OBJECT
public:
    UI(int& argc, char**& argv);
    void exec();
    void set_title(QString title);
    void set_artist(QString artist);
    void set_album(QString album);
    void set_year(QString year);
    void set_track(QString track);
    void set_genre(QString track);
    void set_different_titles();
    void set_different_artists();
    void set_different_albums();
    void set_different_years();
    void set_different_tracks();
    void set_different_genres();
    void set_different_artwork();
    QString get_title();
    QString get_artist();
    QString get_album();
    QString get_year();
    QString get_track();
    QString get_genre();
    void set_artwork(QByteArray data);
    void clear_artwork();
    QByteArray get_artwork();
    QStringList selected_files();
signals:
    void selection_changed(QStringList list);
    void btn_save_clicked();
private:
    QApplication m_app;
    QWidget m_root;
    FileList m_file_list;
    QLineEdit m_edit_title;
    QLineEdit m_edit_artist;
    QLineEdit m_edit_album;
    QLineEdit m_edit_year;
    QLineEdit m_edit_track;
    QLineEdit m_edit_genre;
    ArtworkView m_artwork;
    QLabel m_artwork_info;
};
