#ifndef CQUADTREE_H
#define CQUADTREE_H

#include <qt5/QtCore/QScopedPointer>
#include "csettings.h"
#include "cquadtreenode.h"
#include "utility.h"

namespace LOD {
    /*!
     * \brief The CQuadtree class
     * Quadtree implementation.
     */
    class CQuadtree {
    private:
        QScopedPointer<CQuadtreeNode> m_root;                         ///< Pointer to the root node in the tree
        QVector<qreal> m_lod_vis_distance_ratios;                     ///< LOD visibility range distribution
        int m_xvert;
        int m_yvert;
        QSharedPointer<QOpenGLShaderProgram> m_shader_program;
        QVector<QSharedPointer<QOpenGLTexture>> m_textures;
        QSharedPointer<CPlanetHeightmap> m_heightmap;
    public:
        CQuadtree(int x_vert, int y_vert, const QSharedPointer<QOpenGLShaderProgram>& shader_program,
                  const QVector<QSharedPointer<QOpenGLTexture>>& textures, const QSharedPointer<CPlanetHeightmap>& heightmap);
        /*!
         * \brief           Initialises the tree
         * \param[in]       settings_ptr        different system settings
         */
        void init();
        /*!
         * \brief           Launches a recursive tree traversal
         * \param[out]      selection           selected area representation
         */
        void select(Math::ECubeFace face, float min_height, float max_height, float radius);
    };
}

#endif // CQUADTREE_H
