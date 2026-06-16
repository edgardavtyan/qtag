#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include "ui.hpp"

UI::UI(int& argc, char**& argv): m_app(argc, argv) {
    QHBoxLayout *toolbar_box = new QHBoxLayout();

    QVBoxLayout *main_box = new QVBoxLayout(&m_root);
    main_box->addLayout(toolbar_box);
    main_box->addWidget(&m_file_list);
}

void UI::exec() {
    m_root.show();
    m_app.exec();
}
