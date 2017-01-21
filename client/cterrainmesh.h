#ifndef CTERRAINMESH_H
#define CTERRAINMESH_H

#define CUBE_FACES 6
#define HEIGHTMAP_TEXTURE_OFFSET 1

#include "cmesh.h"
#include "cplanetheightmap.h"
#include "CDLOD/cterrain.h"

/*!
 * \brief The CTerrainMesh class
 * Represents the terrain mesh
 */
class CTerrainMesh : public CMesh {
private:
    QVector<CMesh::SVertexPosition> m_vertices_position;              ///< Vertex buffer for rendering
    QVector<int> m_cube_face_num;                                     ///< Geometry stuff, necessary for shader
    QVector<CMesh::SVertexTextureCoords> m_vert_tex_coords;           ///< Texture coordinates buffer for rendering
    QVector<QSharedPointer<QOpenGLTexture>> m_textures;               ///< Planet textures
    QSharedPointer<CPlanetHeightmap> m_heightmap;                     ///< Height map for generating our landscape
    QScopedPointer<CDLOD::CTerrain> m_cdlod_terrain;                  ///< CDLOD algorithm
    float m_sphere_radius;                                              ///< Planet radius

    /*!
     * \brief Maps unit cube's face to the part of the sphere
     */
    void _create_sphere_faces();
    /*!
     * \brief Obtains the heightmap filename
     * \return          filename
     */
    QString _filename() const;
    /*!
     * \brief Creates planet textures
     */
    void _load_textures();
public:
    CTerrainMesh(const QVector<QSharedPointer<QOpenGLTexture> >& textures, const QString& vertex_shader,
                 const QString& fragment_shader, float radius);
    CTerrainMesh(const QVector<QSharedPointer<QOpenGLTexture> >& textures, const QString& vertex_shader,
                 const QString& fragment_shader, float radius, int seed);
    /*!
     * \brief Inits all buffers
     */
    virtual void init();
    /*!
     * \brief Returns planet seed
     * \return          seed
     */
    int seed() const;
    /*!
     * \brief Renders the terrain mesh
     */
    virtual void render();
};

#endif // CTERRAINMESH_H
