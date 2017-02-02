#ifndef CTERRAINMESHCHUNK_H
#define CTERRAINMESHCHUNK_H

#define CUBE_FACES 6
#define HEIGHTMAP_TEXTURE_OFFSET 1

#include <qt5/QtCore/QSharedPointer>
#include <qt5/QtGui/QOpenGLFunctions>
#include "irenderable.h"
#include "cmesh.h"
#include "cplanetheightmap.h"

/*!
 * \brief The CTerrainMeshChunk class
 * Represents the terrain mesh chunk
 */
class CTerrainMeshChunk : public CMesh {
private:
    Math::ECubeFace m_face;                                           ///< Geometry stuff, necessary for shader
    static QSharedPointer<CPlanetHeightmap> m_heightmap;              ///< Pointer to the heightmap
    QString m_init_error;                                             ///< Initialization error
    QVector<SVertexPosition> m_vertices_position;                     ///< Vertex buffer
    QVector<SVertexTextureCoords> m_vert_tex_coords;                  ///< Texture coordinates buffer
    QSharedPointer<QOpenGLContext> m_context;                         ///< OpenGL context

    /*!
     * \brief Generates unit cube grid
     * \param[in]   x_vert          number of vertices, generated along the x-axis
     * \param[in]   y_vert          number of vertices, generated along the y-axis
     * \param[in]   cube_face       number of cube's face
     */
    void _generate_grid(int x_vert, int y_vert, Math::ECubeFace cube_face);
    /*!
     * \brief Loads planet textures
     */
    void _load_textures();
public:
    CTerrainMeshChunk(const QSharedPointer<QOpenGLShaderProgram>& shader_program,
                      const QVector<QSharedPointer<QOpenGLTexture> >& textures,
                      const QSharedPointer<CPlanetHeightmap>& heightmap,
                      const QSharedPointer<QOpenGLContext>& context);
    virtual ~CTerrainMeshChunk() {}
    /*!
     * \brief Creates all buffers
     * \param[in]   x_vert          number of vertices, generated along the x-axis
     * \param[in]   y_vert          number of vertices, generated along the y-axis
     * \param[in]   cube_face       number of cube's face
     * \param[in]   radius          planet radius
     */
    bool create(int x_vert, int y_vert, Math::ECubeFace cube_face, int radius);
    /*!
     * \brief Renders this terrain mesh chunk
     */
    virtual void render();
    /*!
     * \brief Returns init error
     * \return      init error
     */
    QString error() const;
    /*!
     * \brief Sets scale parameter in shader
     * \param   scale
     */
    void set_scale(float scale);
};

#endif // CTERRAINMESH_H
