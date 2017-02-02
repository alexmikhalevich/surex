#ifndef CQUADTREENODE_H
#define CQUADTREENODE_H

#include <qt5/QtCore/qmath.h>
#include <qt5/QtCore/QSharedPointer>
#include "cterrainmeshchunk.h"
#include "ccamera.h"

namespace LOD {
    /*!
     * \brief The ESelectionResult enum
     * Represents the status of the select operation
     */
    enum ESelectionResult {
        OUT_OF_FRUSTUM,
        OUT_OF_RANGE,
        SELECTED,
        UNDEFINED
    };

    /*!
     * \brief The CQuadtreeNode class
     * The Quadtree node representation
     */
    class CQuadtreeNode {
    private:
        QScopedPointer<CQuadtreeNode> m_top_left;               ///< Top left child
        QScopedPointer<CQuadtreeNode> m_bottom_left;            ///< Bottom left child
        QScopedPointer<CQuadtreeNode> m_top_right;              ///< Top right child
        QScopedPointer<CQuadtreeNode> m_bottom_right;           ///< Bottom right child
        static Math::ECubeFace m_face;                          ///< The number of processed cube face
        static float m_min_height;                              ///< Min height, possible on this planet (normalized)
        static float m_max_height;                              ///< Max height, possible on this planet (normalized)
        static QSharedPointer<CTerrainMeshChunk> m_mesh_chunk;  ///< Mesh chunk which corresponds to the current node
        static QSharedPointer<CCamera> m_camera;                ///< Camera object
        static int m_selection_size;                            ///< Current selection size

        /*!
         * \brief Returns the bounding box for the terrain chunk, which corresponds to the current plane chunk
         * \param[in]       x       x-coordinate of the top left on the plane
         * \param[in]       y       y-coordinate of the top left on the plane
         * \param[in]       size    length of the 2D bounding box side
         * \return          bounding box for the terrain chunk
         */
        Math::CBoundingBox _get_bounding_box(int x, int y, int size) const;

        /*!
         * \brief Generates mesh grid
         * \param[in]   x_vert          number of vertices, generated along the x-axis
         * \param[in]   y_vert          number of vertices, generated along the y-axis
         * \param[in]   shader_program  shader program object instance
         * \param[in]   textures        textures which will be used for this chunk
         * \param[in]   heightmap       heightmap
         * \return                      operation status
         */
        bool _generate_mesh_chunk(int x_vert, int y_vert, QSharedPointer<QOpenGLShaderProgram>& shader_program,
                                  const QVector<QSharedPointer<QOpenGLTexture> >& textures,
                                  const QSharedPointer<CPlanetHeightmap>& heightmap);
    public:
        CQuadtreeNode(Math::ECubeFace face, float min_height, float max_height, float radius, const QSharedPointer<CCamera>& camera);
        /*!
         * Recursively traverses the quadtree to render only visible parts of the terrain mesh.
         * If argument is not listed here, look for CQuadtreeNode::_generate_mesh_chunk() method.
         * \param[in]   parent_in_frustum  flag which shows if the parent node is in frustum
         * \param[in]   x                  x-coordinate of the top-left corner of the parent node
         * \param[in]   y                  y-coordinate of the top-left corner of the parent node
         * \param[in]   lod                level of detail for the parent node
         * \param[in]   size               size of the parent node's bounding square
         * \return                         operation status
         */
        ESelectionResult select(bool parent_in_frustum, int x, int y, short lod, int size,
                                int x_vert, int y_vert, QSharedPointer<QOpenGLShaderProgram>& shader_program,
                                const QVector<QSharedPointer<QOpenGLTexture> >& textures,
                                const QSharedPointer<CPlanetHeightmap>& heightmap);
    };
}

#endif // CQUADTREENODE_H
