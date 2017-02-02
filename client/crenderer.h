#ifndef CRENDERER_H
#define CRENDERER_H

#include <qt5/QtCore/QVector>
#include <qt5/QtCore/QScopedPointer>
#include <qt5/QtGui/QOpenGLContext>
#include <qt5/QtGui/QOpenGLPaintDevice>
#include <qt5/QtGui/QOpenGLFunctions>
#include <qt5/QtGui/QSurfaceFormat>
#include "cscene.h"
#include "csettings.h"

/*!
 * \brief The CRenderer class
 * Provides all necessary funtionality for rendering.
 */
class CRenderer
{
private:
    QSharedPointer<QOpenGLContext> m_context;
    QScopedPointer<QOpenGLPaintDevice> m_device;
    QObject* m_window_ptr;
public:
    CRenderer(const QSize& window_size, QObject* context_parent);
    /*!
     * \brief Render scene
     * \param[in]           scene_ptr           pointer to the scene instance which will be rendered
     */
    void render_scene(const QScopedPointer<CScene>& scene_ptr);
    /*!
     * \brief Returns openGL paint device
     * \return                              pointer to the openGL paint device
     */
    QScopedPointer<QOpenGLPaintDevice> device();
    /*!
     * \brief Swap the back and front buffers of surface
     * \param[in]            surface
     */
    void swap_buffers(QSurface* surface);
};

#endif // CRENDERER_H
