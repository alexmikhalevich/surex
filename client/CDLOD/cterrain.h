#ifndef CTERRAIN_H
#define CTERRAIN_H

#include <qt5/QtGui/QOpenGLTexture>
#include "cquadtree.h"
#include "cselection.h"
#include "csettings.h"
#include "ccamera.h"

namespace CDLOD {
    /*!
     * \brief The CTerrain class
     * Represents the terrain which is rendered with the help of CDLOD algorithm.
     */
    class CTerrain {
    private:
        CQuadtree m_quadtree;                               ///< CQuadtree instance for processing
        CSelection m_selection;                             ///< CSelection instance which represents the current area selected for rendering
        CSettings m_settings;                               ///< CSettings instance which holds all system parameters
        QScopedPointer<QOpenGLTexture> m_height_map;        ///< Pointer to the given height map
    public:
        CTerrain();
    };
}

#endif // CTERRAIN_H
