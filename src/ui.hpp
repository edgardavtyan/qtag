#pragma once

#include <QApplication>
#include <QWidget>
#include <QListView>
#include <QLineEdit>
#include "file_list.hpp"

class UI : public QObject {
    Q_OBJECT
public:
    UI(int& argc, char**& argv);
    void exec();
    void set_title(QString title);
    void set_artist(QString artist);
    void set_album(QString album);
    void set_date(QString date);
    void set_different_titles();
    void set_different_artists();
    void set_different_albums();
    void set_different_dates();
    QString get_title();
    QString get_artist();
    QString get_album();
    uint get_date();
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
    QLineEdit m_edit_date;
};
