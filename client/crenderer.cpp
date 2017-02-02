#include "crenderer.h"

CRenderer::CRenderer(const QSize& window_size, QOpenGLContext* opengl_context) {
    m_device = QSharedPointer<QOpenGLPaintDevice>(new QOpenGLPaintDevice);
    m_device->setSize(window_size);

    m_opengl_funcs = new QOpenGLFunctions(opengl_context);
    m_opengl_funcs->initializeOpenGLFunctions();
}

void CRenderer::render_scene(const QSharedPointer<CScene>& scene_ptr) {
    m_opengl_funcs->glClearColor(0.0f, 0.0f, 255.0f, 10.0f);
    m_opengl_funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    scene_ptr->render();
}

QSharedPointer<QOpenGLPaintDevice> CRenderer::device() {
    return m_device;
}
