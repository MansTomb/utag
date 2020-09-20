set(SOURCES
    mainwindow.ui mainwindow.cpp mainwindow.h
    droptablewidget.cpp droptablewidget.h
    DirProcess.cpp DirProcess.h
    tagger.cpp tagger.h
    logger.cpp logger.h
    dropdialog.ui dropdialog.cpp dropdialog.h
)

link_directories(../../3dparty/taglib/build/lib)


add_library(src ${SOURCES})
target_link_libraries(src PRIVATE Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        libtag.a
)
