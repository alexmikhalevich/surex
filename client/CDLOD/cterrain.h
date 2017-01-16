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
        QScopedPointer<CQuadtree> m_quadtree;               ///< Pointer to the CQuadtree instance for processing
        QSharedPointer<CSelection> m_selection;             ///< Pointer to the CSelection instance which represents the current area selected for rendering
        QSharedPointer<CSettings> m_settings;               ///< Pointer to the CSettings instance which holds all system parameters
        QSharedPointer<QOpenGLTexture> m_height_map;        ///< Pointer to the given height map
    public:
        CTerrain(QSharedPointer<CCamera>& camera, QSharedPointer<QOpenGLTexture>& height_map, QSharedPointer<CSettings>& settings);
        /*!
         * \brief       Launches LOD selection process
         */
        void select_lod();
        /*!
         * \brief       Returns pointer to the calculated selection
         * \return      Pointer to the selection
         */
        QSharedPointer<CSelection> get_selection();
    };
}

#endif // CTERRAIN_H
