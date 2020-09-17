set(SOURCES mainwindow.cpp mainwindow.h mainwindow.ui
        droplabel.cpp droplabel.h
        filedropframe.cpp filedropframe.h
        fileutils.cpp fileutils.h
        mp3tag.cpp mp3tag.h)

add_library(src ${SOURCES})
target_link_libraries(src PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
