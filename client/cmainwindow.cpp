#include "cmainwindow.h"

CMainWindow::CMainWindow(QWindow* parent) : QWindow(parent), m_context(0), m_device(0), m_update_pending(false) {
	setSurfaceType(QWindow::OpenGLSurface);
    m_settings.reset(new CSettings);
}

CMainWindow::~CMainWindow() {
}

void CMainWindow::render(QPainter* painter) {
	Q_UNUSED(painter);
}

void CMainWindow::render() {
	if(!m_device)
		m_device = new QOpenGLPaintDevice;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    m_device->setSize(size());
    QPainter painter(m_device);
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
    bool needs_init = false;
    if(!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();
        needs_init = true;
    }
    m_context->makeCurrent(this);
    if(needs_init) {
        initializeOpenGLFunctions();
        initialize();
    }
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
