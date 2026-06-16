#pragma once

#include <QApplication>
#include <QWidget>
#include <QListView>
#include "file_list.hpp"

class UI : public QObject {
    Q_OBJECT
public:
    UI(int& argc, char**& argv);
    void exec();
signals:
private:
    QApplication m_app;
    QWidget m_root;
    FileList m_file_list;
};
