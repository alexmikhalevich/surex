#include "cmainwindow.h"

CMainWindow::CMainWindow(QWindow* parent) : QWindow(parent), m_update_pending(false) {
    setSurfaceType(QWindow::OpenGLSurface);

    m_context = QSharedPointer<QOpenGLContext>(new QOpenGLContext(this));
    m_context->setFormat(requestedFormat());
    m_context->create();
    m_context->makeCurrent(this);

    m_engine = QSharedPointer<CMainEngine>(new CMainEngine(size(), m_context));
    initialize();
}

CMainWindow::~CMainWindow() {
}

void CMainWindow::render(QPainter* painter) {
    Q_UNUSED(painter);
}

void CMainWindow::render() {
    m_engine->render();
    QPainter painter(m_engine->device().data());
    render(&painter);
}

void CMainWindow::initialize() {
    QSurfaceFormat surface_format;
    surface_format.setSamples(CSettings::samples_num());
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
    m_context->swapBuffers(this);
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
