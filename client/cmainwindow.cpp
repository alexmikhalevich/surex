#include "cmainwindow.h"

CMainWindow::CMainWindow(QWindow* parent) : QWindow(parent), m_update_pending(false) {
    setSurfaceType(QWindow::OpenGLSurface);
    m_settings.reset(new CSettings);
    m_renderer = QSharedPointer<CRenderer>(new CRenderer(size(), this));
    m_scene = QSharedPointer<CScene>(new CScene());

    initialize();
}

CMainWindow::~CMainWindow() {
}

void CMainWindow::render(QPainter* painter) {
	Q_UNUSED(painter);
}

void CMainWindow::render() {
    m_renderer->render_scene(m_scene);
    QPainter painter(*m_renderer->device());
    render(&painter);
}

void CMainWindow::initialize() {
    QSurfaceFormat surface_format;
    surface_format.setSamples(m_settings->get_samples_num());
    setFormat(surface_format);
}

void CMainWindow::renderLater() {
    if(!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void CMainWindow::renderNow() {
    if(!isExposed())
        return;
    render();
    m_renderer->swap_buffers(this);
}

bool CMainWindow::event(QEvent* event) {
    switch(event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void CMainWindow::exposeEvent(QExposeEvent* event) {
    Q_UNUSED(event);
    if(isExposed())
        renderNow();
}
