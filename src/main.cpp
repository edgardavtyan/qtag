#include <QFileDialog>
#include <QPushButton>
#include "ui.hpp"
#include "taglib/taglib.h"
#include "taglib/fileref.h"
#include "taglib/mpegfile.h"
#include "taglib/id3v2tag.h"
#include "taglib/attachedpictureframe.h"

QByteArray read_artwork(QString file) {
    TagLib::MPEG::File mp3file(file.toStdString().c_str());
    TagLib::ID3v2::Frame *frame = mp3file.ID3v2Tag()->frameListMap()["APIC"].front();
    TagLib::ByteVector pic = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frame)->picture();
    QByteArray data(pic.data(), pic.size());
    return data;
}

int main(int argc, char** argv) {
    UI ui(argc, argv);
    bool is_different_titles = false;
    bool is_different_artists = false;
    bool is_different_albums = false;
    bool is_different_years = false;
    bool is_different_tracks = false;
    bool is_different_artwork = false;

    QObject::connect(&ui, &UI::selection_changed, [&](QStringList list) {
        if (list.isEmpty()) {
            ui.set_title("");
            ui.set_artist("");
            ui.set_album("");
            ui.set_year("");
            ui.set_track("");
            ui.clear_artwork();
            return;
        }

        TagLib::FileRef first_file(list[0].toStdString().c_str());
        TagLib::Tag *first_tag = first_file.tag();
        QString first_title = first_tag->title().toCString();
        QString first_artist = first_tag->artist().toCString();
        QString first_album = first_tag->album().toCString();
        uint first_year = first_tag->year();
        uint first_track = first_tag->track();
        QByteArray first_artwork = read_artwork(list[0]);
        ui.set_title(first_title);
        ui.set_artist(first_artist);
        ui.set_album(first_album);
        ui.set_year(QString::number(first_year));
        ui.set_track(QString::number(first_track));
        ui.set_artwork(first_artwork);

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
            if (tag->track() != first_track) {
                ui.set_different_tracks();
                is_different_tracks = true;
            }

            QByteArray artwork = read_artwork(str);
            if (artwork != first_artwork) {
                ui.set_different_artwork();
                is_different_artwork = true;
            }
        }
    });

    QObject::connect(&ui, &UI::btn_save_clicked, [&]() {
        for (QString &filename : ui.selected_files()) {
            TagLib::FileRef tagfile(filename.toStdString().c_str());
            if (not is_different_titles or not ui.get_title().isEmpty()) {
                tagfile.tag()->setTitle(ui.get_title().toStdString().c_str());
            }
            if (not is_different_artists or not ui.get_artist().isEmpty()) {
                tagfile.tag()->setArtist(ui.get_artist().toStdString().c_str());
            }
            if (not is_different_albums or not ui.get_album().isEmpty()) {
                tagfile.tag()->setAlbum(ui.get_album().toStdString().c_str());
            }
            if (not is_different_years or not ui.get_year().isEmpty()) {
                tagfile.tag()->setYear(ui.get_year().toUInt());
            }
            if (not is_different_tracks or not ui.get_track().isEmpty()) {
                tagfile.tag()->setTrack(ui.get_track().toUInt());
            }
            tagfile.save();

            if (not is_different_artwork) {
                TagLib::MPEG::File mp3file(filename.toStdString().c_str());
                TagLib::ID3v2::Tag *mp3tag = mp3file.ID3v2Tag();
                mp3tag->removeFrame(mp3tag->frameList("APIC")[0], true);
                auto *artwork = new TagLib::ID3v2::AttachedPictureFrame();
                artwork->setType(TagLib::ID3v2::AttachedPictureFrame::FrontCover);
                artwork->setMimeType("image/jpeg");
                artwork->setPicture(TagLib::ByteVector(ui.get_artwork().data(), ui.get_artwork().size()));
                mp3tag->addFrame(artwork);
                mp3file.save();
            }
        }
    });
    ui.exec();
}
