HEADERS     = treeitem.h \
              treemodel.h \
    strparser.h
RESOURCES   = simpletreemodel.qrc
SOURCES     = treeitem.cpp \
              treemodel.cpp \
              main.cpp \
    strparser.cpp
CONFIG  += qt

# install
target.path = $$[QT_INSTALL_EXAMPLES]/itemviews/simpletreemodel
sources.files = $$SOURCES $$HEADERS $$RESOURCES *.pro *.txt
sources.path = $$[QT_INSTALL_EXAMPLES]/itemviews/simpletreemodel
INSTALLS += target sources

symbian: include($$PWD/../../symbianpkgrules.pri)
maemo5: include($$PWD/../../maemo5pkgrules.pri)
contains(MEEGO_EDITION,harmattan): include($$PWD/../../harmattanpkgrules.pri)

