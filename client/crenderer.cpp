#include "crenderer.h"

CRenderer::CRenderer(const QSize& window_size, QObject* context_parent = nullptr, const QSharedPointer<CSettings>& settings) {
    m_window_ptr = context_parent;

    m_device.reset(new QOpenGLPaintDevice);
    m_device->setSize(window_size);

    m_context.reset(new QOpenGLContext(context_parent));
    m_context->setFormat(requestedFormat());
    m_context->create();
    m_context->makeCurrent(m_window_ptr);
    QOpenGLFunctions::initializeOpenGLFunctions();
}

void CRenderer::render_scene(const QScopedPointer<CScene>& scene_ptr) {
    m_context->makeCurrent(m_window_ptr);

    QOpenGLFunctions::glClearColor(0.0f, 0.0f, 255.0f, 10.0f);
    QOpenGLFunctions::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    scene_ptr->render();
}

QScopedPointer<QOpenGLPaintDevice> CRenderer::device() {
    return m_device;
}

void CRenderer::swap_buffers(QSurface* surface) {
    m_context->swapBuffers(surface);
}
