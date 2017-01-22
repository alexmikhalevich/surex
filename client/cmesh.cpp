#include "cmesh.h"

CMesh::CMesh(const QVector<QSharedPointer<QOpenGLTexture>>& textures, const QString& vertex_shader, const QString& fragment_shader) {

    m_init_status = true;
    m_init_error = "";
    if(!m_shader_program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_shader)) {
        m_init_status = false;
        m_init_error += "EE: Unable to compile vertex shader " + vertex_shader + ".";
    }
    if(!m_shader_program.addShaderFromSourceFile(QOpenGLShader::Fragment, fragment_shader)) {
        m_init_status = false;
        m_init_error += "EE: Unable to compile fragment shader " + fragment_shader = ".";
    }
    if(!m_init_status)
        return;

    m_textures = textures;
}

CMesh::CMesh(const QSharedPointer<QOpenGLShaderProgram>& shader_program, const QVector<QSharedPointer<QOpenGLTexture> >& textures) {
    m_shader_program = shader_program;
    m_textures = textures;
}

template<class SVertexType>
bool CMesh::_init_buffer(const QOpenGLBuffer& buffer, const QVector<SVertexType>& data, const QString& buffer_id, int tuple_size, GLenum gl_type) {
    if(!buffer.create())
        return false;
    buffer.bind();
    buffer.allocate(data.constData(), data.size() * sizeof(SVertexType));
    m_shader_program.enableAttributeArray(buffer_id);
    m_shader_program.setAttributeBuffer(buffer_id, gl_type, 0, tuple_size);
    return true;
}

bool CMesh::init(const QVector<SVertexPosition>& vertices_position, const QVector<SVertexTextureCoords>& vertices_tex_coords
                 /*, const QVector<unsigned int>& indices*/) {
    m_vbo_position = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo_position.setUsagePattern(QOpenGLBuffer::StaticDraw);
//    m_vbo_normal = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
//    m_vbo_normal.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo_texture_coords = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo_texture_coords.setUsagePattern(QOpenGLBuffer::StaticDraw);

//    m_ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//    m_ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);

    if(!m_vao.create()) {
        m_init_error = "EE: Unable to create VAO.";
        return false;
    }
    m_vao.bind();

    if(!_init_buffer<SVertexPosition>(m_vbo_position, vertices_position, "vertex", 3, GL_FLOAT)) {
        m_init_error = "EE: Unable to create position VBO.";
        return false;
    }
//    if(!_init_buffer<SVertexNormal>(m_vbo_normal, vertices_normal, "vertex_normal", 3, GL_FLOAT)) {
//        m_init_error = "EE: Unable to create normal VBO.";
//        return false;
//    }
    if(!_init_buffer<SVertexTextureCoords>(m_vbo_texture_coords, vertices_tex_coords, "vertex_tex_coords", 2, GL_FLOAT)) {
        m_init_error = "EE: Unable to create texture VBO.";
        return false;
    }
//    if(m_ibo.create()) {
//        m_ibo.bind();
//        m_ibo.allocate(indices.constData(), indices.size() * sizeof(unsigned int));
//    }
//    else {
//        m_init_error = "EE: Unable to create IBO.";
//        return false;
//    }
    m_vao.release();
//    m_indices_size = indices.size();

    return true;
}

bool CMesh::create_successfull() const {
    return m_init_status;
}

QString CMesh::error() const {
    return m_init_error;
}

void CMesh::render() {
    for(size_t i = 0; i < m_textures.size(); ++i) {
        QOpenGLFunctions::glActiveTexture(m_textures.at(i)->textureId());
        m_shader_program.setUniformValue("material_" + QString::number(i), i);
        m_textures[i]->bind();
    }
    QOpenGLFunctions::glActiveTexture(GL_TEXTURE0);

    m_vao.bind();
    QOpenGLFunctions::glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, 0);
    m_vao.release();
}

QOpenGLShaderProgram& CMesh::shader() {
    return m_shader_program;
}
