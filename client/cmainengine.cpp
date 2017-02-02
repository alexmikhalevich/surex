#include "cmainengine.h"

CMainEngine::CMainEngine(const QSize& window_size, const QSharedPointer<QOpenGLContext>& context) {
    m_renderer = QSharedPointer<CRenderer>(new CRenderer(window_size, context.data()));
    m_scene = QSharedPointer<CScene>(new CScene());

    m_state = ERenderState::MAIN_MENU;

    //NOTE: only for testing purposes
    m_state = ERenderState::SCENE;
    QSharedPointer<CPlanet> planet(new CPlanet(m_scene->camera(), context, 321));
    m_scene->add_object(planet);
    /////////////////////////////////
}

void CMainEngine::render() {
    switch(m_state) {
    case ERenderState::MAIN_MENU:
        //TODO: menu rendering
        break;
    case ERenderState::SCENE:
        m_renderer->render_scene(m_scene);
        break;
    }
}

QSharedPointer<QOpenGLPaintDevice> CMainEngine::device() {
    return m_renderer->device();
}
