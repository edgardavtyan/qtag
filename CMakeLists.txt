cmake_minimum_required(VERSION 3.16)

project(qtag VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(
    qtag
    main.qrc
    src/main.cpp
    src/ui.cpp
    src/file_model.cpp
    src/file_list.cpp
    src/artwork_view.cpp
)

target_link_libraries(qtag PRIVATE Qt6::Core Qt6::Widgets tag)

#install(TARGETS qplay DESTINATION /usr/bin)
#install(FILES dist/qplay.desktop DESTINATION /usr/share/applications)
#install(FILES dist/qplay.svg DESTINATION /usr/share/icons)
