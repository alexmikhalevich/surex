QT += core gui

TARGET = surex

SOURCES += main.cpp \
	cmainwindow.cpp \
    csettings.cpp \
    ccamera.cpp \
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
    csimplexnoise.cpp \
    cterrainmesh.cpp

HEADERS += cmainwindow.h \
    csettings.h \
    ccamera.h \
    CDLOD/cquadtree.h \
    CDLOD/cquadtreenode.h \
    CDLOD/cselection.h \
    utility.h \
    CDLOD/cterrain.h \
    cmesh.h \
    crenderer.h \
    cscene.h \
    cplanetheightmap.h \
    cplanet.h \
    iserializable.h \
    csimplexnoise.h \
    cterrainmesh.h \
    irenderable.h

DISTFILES += \
    shaders/planet.frag \
    shaders/planet.vert
