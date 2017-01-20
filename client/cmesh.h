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
#include "irenderable.h"

/*!
 * \brief The CMesh class
 * Mesh representation
 */
class CMesh : public IRenderable {
public:
    /*!
     * \brief The SVertexPosition struct
     * Mesh vertex position
     */
    struct SVertexPosition {
        float _x;
        float _y;
        float _z;
        SVertexPosition() {}
        SVertexPosition(float x, float y, float z) : _x(x), _y(y), _z(z) {}
        SVertexPosition(const QVector3D& pos) : _x(pos.x()), _y(pos.y()), _z(pos.z()) {}
    };
    /*!
     * \brief The SVertexNormal struct
     * Mesh vertex normal
     */
    struct SVertexNormal {
        float _x;
        float _y;
        float _z;
        SVertexNormal() {}
        SVertexNormal(float x, float y, float z) : _x(x), _y(y), _z(z)  {}
        SVertexNormal(const QVector3D& pos) : _x(pos.x()), _y(pos.y()), _z(pos.z()) {}
    };
    /*!
     * \brief The SVertexTextureCoords struct
     * Mesh vertex texture coordinates
     */
    struct SVertexTextureCoords {
        float _x;
        float _y;
        SVertexTextureCoords() {}
        SVertexTextureCoords(float x, float y) : _x(x), _y(y) {}
    };
protected:
    QOpenGLBuffer m_vbo_position;                                   ///< Vertex buffer object for positions
    QOpenGLBuffer m_vbo_texture_coords;                             ///< Vertex buffer object for texture coordinates
    QVector<QSharedPointer<QOpenGLTexture>> m_textures;             ///< Textures of the current mesh
    QOpenGLVertexArrayObject m_vao;                                 ///< Vertex array object
    QOpenGLShaderProgram m_shader_program;                          ///< Shader program for the current mesh
private:
    //QOpenGLBuffer m_vbo_normal;                                     ///< Vertex buffer object for normals
    //QOpenGLBuffer m_ibo;                                            ///< Index buffer object
    bool m_init_status;                                             ///< Shows if there were errors while mesh initialization
    QString m_init_error;                                           ///< Keeps error text if it occurs
    //GLsizei m_indices_size;                                         ///< Number of indices, used in mesh rendering

    /*!
     *  \brief   Inits the given buffer
     *  \param[out]         buffer              buffer which will be initialized
     *  \param[in]          data                data for initialization
     *  \param[in]          buffer_id           identifier for the buffer in the shader program
     *  \param[in]          tuple_size          number of fields in SVertexType struct
     *  \param[in]          gl_type             buffer elements type
     *  \return                                 operation status: false if buffer creation failes
     */
    template<class SVertexType>
    bool _init_buffer(QOpenGLBuffer& buffer, const QVector<SVertexType>& data, const QString& buffer_id, int tuple_size, GLenum gl_type);
public:
    CMesh(const QVector<QSharedPointer<QOpenGLTexture>>& textures, const QString& vertex_shader, const QString& fragment_shader);
    /*!
     * \brief   Inits all buffers
     * \param               vertices_position   vertex buffer
     * \param               vertices_tex_coords texture coordinates buffer
     * \param               indices             index buffer
     * \return                                  operation status: false if any buffer creation operation fails
     */
    virtual bool init(const QVector<SVertexPosition>& vertices_position, const QVector<SVertexTextureCoords>& vertices_tex_coords
              /*, const QVector<unsigned int>& indices*/);
    /*!
     * \brief     Render mesh
     */
    virtual void render();
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
    /*!
     * \brief Returns reference to the shader program instance
     * \return
     */
    QOpenGLShaderProgram& shader();
};

#endif // CMESH_H
