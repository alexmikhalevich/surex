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
        QSharedPointer<CCamera> m_camera;                             ///< Camera object
    public:
        CQuadtree(int x_vert, int y_vert, const QSharedPointer<QOpenGLShaderProgram>& shader_program,
                  const QVector<QSharedPointer<QOpenGLTexture>>& textures, const QSharedPointer<CPlanetHeightmap>& heightmap,
                  const QSharedPointer<CCamera>& camera);
        /*!
         * \brief           Initialises the tree
         */
        void init();
        /*!
         * \brief           Launches a recursive tree traversal
         * \param[in]       face                cube face identifier
         * \param[in]       min_height          minimum planet height
         * \param[in]       max_height          maximum planet height
         * \param[in]       radius              planet radius
         */
        void select(Math::ECubeFace face, float min_height, float max_height, int radius);
    };
}

#endif // CQUADTREE_H
