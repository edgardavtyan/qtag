#include <QFileDialog>
#include <QPushButton>
#include "ui.hpp"
#include "taglib/taglib.h"
#include "taglib/fileref.h"

int main(int argc, char** argv) {
    UI ui(argc, argv);
    bool is_different_titles = false;
    bool is_different_artists = false;
    bool is_different_albums = false;
    bool is_different_years = false;

    QObject::connect(&ui, &UI::selection_changed, [&](QStringList list) {
        TagLib::FileRef first_file(list[0].toStdString().c_str());
        TagLib::Tag *first_tag = first_file.tag();
        QString first_title = first_tag->title().toCString();
        QString first_artist = first_tag->artist().toCString();
        QString first_album = first_tag->album().toCString();
        uint first_year = first_tag->year();
        ui.set_title(first_title);
        ui.set_artist(first_artist);
        ui.set_album(first_album);
        ui.set_year(QString::fromStdString(std::to_string(first_year)));
        for (QString &str : list) {
            TagLib::FileRef file(str.toStdString().c_str());
            TagLib::Tag *tag = file.tag();
            if (QString(tag->title().toCString()) != first_title) {
                ui.set_different_titles();
                is_different_titles = true;
            }
            if (QString(tag->artist().toCString()) != first_artist) {
                ui.set_different_artists();
                is_different_artists = true;
            }
            if (QString(tag->album().toCString()) != first_album) {
                ui.set_different_albums();
                is_different_albums = true;
            }
            if (tag->year() != first_year) {
                ui.set_different_years();
                is_different_years = true;
            }
        }
    });

    QObject::connect(&ui, &UI::btn_save_clicked, [&]() {
        for (QString &filename : ui.selected_files()) {
            TagLib::FileRef tagfile(filename.toStdString().c_str());
            if (not is_different_titles) {
                tagfile.tag()->setTitle(ui.get_title().toStdString().c_str());
            }
            if (not is_different_artists) {
                tagfile.tag()->setArtist(ui.get_artist().toStdString().c_str());
            }
            if (not is_different_albums) {
                tagfile.tag()->setAlbum(ui.get_album().toStdString().c_str());
            }
            if (not is_different_years) {
                tagfile.tag()->setYear(ui.get_year());
            }
            tagfile.save();
        }
    });
    ui.exec();
}
