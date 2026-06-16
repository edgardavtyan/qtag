#include <QFileDialog>
#include <QPushButton>
#include "ui.hpp"
#include "taglib/taglib.h"
#include "taglib/fileref.h"

int main(int argc, char** argv) {
    UI ui(argc, argv);
    QObject::connect(&ui, &UI::selection_changed, [&](QStringList list) {
        TagLib::FileRef first_file(list[0].toStdString().c_str());
        TagLib::Tag *first_tag = first_file.tag();
        QString first_title = first_tag->title().toCString();
        QString first_artist = first_tag->artist().toCString();
        QString first_album = first_tag->album().toCString();
        uint first_date = first_tag->year();
        ui.set_title(first_title);
        ui.set_artist(first_artist);
        ui.set_album(first_album);
        ui.set_date(QString::fromStdString(std::to_string(first_date)));
        for (QString &str : list) {
            TagLib::FileRef file(str.toStdString().c_str());
            TagLib::Tag *tag = file.tag();
            if (QString(tag->title().toCString()) != first_title) {
                ui.set_different_titles();
            }
            if (QString(tag->artist().toCString()) != first_artist) {
                ui.set_different_artists();
            }
            if (QString(tag->album().toCString()) != first_album) {
                ui.set_different_albums();
            }
            if (tag->year() != first_date) {
                ui.set_different_dates();
            }
        }
    });
    ui.exec();
}
