QT += core gui

TARGET = surex

SOURCES += main.cpp \
	cmainwindow.cpp \
    csettings.cpp \
    cquadtree.cpp \
    cselection.cpp \
    ccamera.cpp \
    cquadtreenode.cpp \
    CDLOD/cquadtree.cpp \
    CDLOD/cquadtreenode.cpp \
    CDLOD/cselection.cpp \
    utility.cpp \
    CDLOD/cterrain.cpp \
    cmesh.cpp \
    crenderer.cpp \
    cscene.cpp \
    cplanetheightmap.cpp \
    cplanet.cpp \
    csimplexnoise.cpp

HEADERS += cmainwindow.h \
    csettings.h \
    cquadtree.h \
    cselection.h \
    ccamera.h \
    cquadtreenode.h \
    CDLOD/cquadtree.h \
    CDLOD/cquadtreenode.h \
    CDLOD/cselection.h \
    utility.h \
    CDLOD/cterrain.h \
    cmesh.h \
    irenderingobject.h \
    crenderer.h \
    cscene.h \
    cplanetheightmap.h \
    cplanet.h \
    iserializable.h \
    csimplexnoise.h
