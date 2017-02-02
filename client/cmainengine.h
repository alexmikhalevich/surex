#ifndef CMAINENGINE_H
#define CMAINENGINE_H

#include <qt5/QtCore/QSharedPointer>
#include <qt5/QtGui/QOpenGLPaintDevice>
#include "crenderer.h"
#include "cplanet.h"

class CMainEngine {
private:
    enum ERenderState {
        MAIN_MENU,
        SCENE
    };

    QSharedPointer<CRenderer> m_renderer;
    QSharedPointer<CScene> m_scene;
    ERenderState m_state;
public:
    CMainEngine(const QSize& window_size, const QSharedPointer<QOpenGLContext>& context);
    void render();
    QSharedPointer<QOpenGLPaintDevice> device();
};

#endif // CMAINENGINE_H
