#ifndef CMESH_H
#define CMESH_H

#include <qt5/QtCore/QVector>
#include <qt5/QtGui/QOpenGLTexture>
#include <qt5/QtCore/QScopedPointer>
#include <qt5/QtGui/QVector3D>
#include <qt5/QtGui/QVector2D>
#include <qt5/QtGui/QOpenGLShaderProgram>
#include <qt5/QtGui/QOpenGLVertexArrayObject>
#include <qt5/QtGui/QOpenGLBuffer>
#include <qt5/QtGui/QOpenGLFunctions>

/*!
 * \brief The CMesh class
 * Mesh representation
 */
class CMesh {
public:
    /*!
     * \brief The SVertexPosition struct
     * Mesh vertex position
     */
    struct SVertexPosition {
        float x;
        float y;
        float z;
    };
    /*!
     * \brief The SVertexNormal struct
     * Mesh vertex normal
     */
    struct SVertexNormal {
        float x;
        float y;
        float z;
    };
    /*!
     * \brief The SVertexTextureCoords struct
     * Mesh vertex texture coordinates
     */
    struct SVertexTextureCoords {
        float x;
        float y;
    };

private:
    QVector<QSharedPointer<QOpenGLTexture>> m_textures;             ///< Textures of the current mesh
    QOpenGLBuffer m_vbo_position;                                   ///< Vertex buffer object for positions
    QOpenGLBuffer m_vbo_normal;                                     ///< Vertex buffer object for normals
    QOpenGLBuffer m_vbo_texture_coords;                             ///< Vertex buffer object for texture coordinates
    QOpenGLBuffer m_ibo;                                            ///< Index buffer object
    QOpenGLVertexArrayObject m_vao;                                 ///< Vertex array object
    QOpenGLShaderProgram m_shader_program;                          ///< Shader program for the current mesh
    bool m_init_status;                                             ///< Shows if there were errors while mesh initialization
    QString m_init_error;                                           ///< Keeps error text if it occurs
    GLsizei m_indices_size;                                         ///< Number of indices, used in mesh rendering

    /*!
     *  \brief   Inits the given buffer
     *  \param[out]     buffer      buffer which will be initialized
     *  \param[in]      data        data for initialization
     *  \param[in]      buffer_id   identifier for the buffer in the shader program
     *  \param[in]      tuple_size  number of fields in SVertexType struct
     *  \param[in]      gl_type     buffer elements type
     *  \return                     operation status: false if buffer creation failes
     */
    template<class SVertexType>
    bool _init_buffer(QOpenGLBuffer& buffer, const QVector<SVertexType>& data, const QString& buffer_id, int tuple_size, GLenum gl_type);
public:
    CMesh(const QVector<SVertexPosition>& vertices_position, const QVector<SVertexNormal>& vertices_normal,
          const QVector<SVertexTextureCoords>& vertices_tex_coords, const QVector<unsigned int>& indices,
          const QVector<QSharedPointer<QOpenGLTexture>>& textures, const QString& vertex_shader, const QString& fragment_shader);
    /*!
     * \brief     Render mesh
     */
    void render();
    /*!
     * \brief     Returns creation status
     * \return                      creation status: false if create() function failed
     */
    bool create_successfull() const;
    /*!
     * \brief     Returns error description
     * \return                      error description
     */
    QString error() const;
};

#endif // CMESH_H