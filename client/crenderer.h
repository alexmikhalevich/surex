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
    QSharedPointer<QOpenGLPaintDevice> m_device;
    QOpenGLFunctions* m_opengl_funcs;
    QObject* m_window_ptr;
public:
    CRenderer(const QSize& window_size, QOpenGLContext* opengl_context);
    /*!
     * \brief Render scene
     * \param[in]           scene_ptr           pointer to the scene instance which will be rendered
     */
    void render_scene(const QSharedPointer<CScene>& scene_ptr);
    /*!
     * \brief Returns openGL paint device
     * \return                                  pointer to the openGL paint device
     */
    QSharedPointer<QOpenGLPaintDevice> device();
};

#endif // CRENDERER_H
