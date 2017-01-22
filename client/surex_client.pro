QT += core gui

TARGET = surex

SOURCES += main.cpp \
	cmainwindow.cpp \
    csettings.cpp \
    ccamera.cpp \
    CDLOD/cquadtree.cpp \
    CDLOD/cquadtreenode.cpp \
    utility.cpp \
    cmesh.cpp \
    crenderer.cpp \
    cscene.cpp \
    cplanetheightmap.cpp \
    cplanet.cpp \
    csimplexnoise.cpp \
    cterrainmeshchunk.cpp

HEADERS += cmainwindow.h \
    csettings.h \
    ccamera.h \
    CDLOD/cquadtree.h \
    CDLOD/cquadtreenode.h \
    utility.h \
    cmesh.h \
    crenderer.h \
    cscene.h \
    cplanetheightmap.h \
    cplanet.h \
    iserializable.h \
    csimplexnoise.h \
    irenderable.h \
    cterrainmeshchunk.h

DISTFILES += \
    shaders/planet.frag \
    shaders/planet.vert
