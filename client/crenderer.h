#ifndef CRENDERER_H
#define CRENDERER_H

#include <qt5/QtCore/QVector>
#include <qt5/QtCore/QScopedPointer>
#include "cscene.h"

/*!
 * \brief The CRenderer class
 * Provides all necessary funtionality for rendering.
 */
class CRenderer
{
public:
    CRenderer();
    /*!
     * \brief Render scene
     * \param           scene_ptr           pointer to the scene instance which will be rendered
     */
    void render_scene(const QScopedPointer<CScene>& scene_ptr);
};

#endif // CRENDERER_H
