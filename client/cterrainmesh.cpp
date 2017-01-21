#include "cterrainmesh.h"

CTerrainMesh::CTerrainMesh(const QVector<QSharedPointer<QOpenGLTexture>>& textures, const QString& vertex_shader,
                           const QString& fragment_shader, float radius)
    : CMesh(textures, vertex_shader, fragment_shader) {

    if(!create_successfull()) {
        //TODO: process this error
    }

    m_heightmap = QSharedPointer<CPlanetHeightmap>(new CPlanetHeightmap(_filename()));
    m_sphere_radius = radius;
}

CTerrainMesh::CTerrainMesh(const QVector<QSharedPointer<QOpenGLTexture>>& textures, const QString& vertex_shader,
                           const QString& fragment_shader, float radius, int seed)
    : CMesh(textures, vertex_shader, fragment_shader) {

    if(!create_successfull()) {
        //TODO: process this error
    }

    m_heightmap = QSharedPointer<CPlanetHeightmap>(new CPlanetHeightmap(seed));
    m_heightmap->generate(CSettings::details() * CSettings::details() * CUBE_FACES);
    m_sphere_radius = radius;
}

void CTerrainMesh::_create_sphere_faces() {
    int width = CSettings::details();
    int height = CSettings::details();
    QVector3D position;

    for(int u = 0; u < width; ++u) {
        for(int v = 0; v < height; ++v) {
            position = QVector3D(-1.0, -1.0, -1.0);
            //u = x; v = y
            position.setX((qreal)u / (qreal)(CSettings::details() - 1) * 2.0);
            position.setY((qreal)v / (qreal)(CSettings::details() - 1) * 2.0);
            m_vertices_position.append(position);
            m_cube_face_num.append(1);
            //u = x; v = z
            position.setX((qreal)u / (qreal)(CSettings::details() - 1) * 2.0);
            position.setZ((qreal)v / (qreal)(CSettings::details() - 1) * 2.0);
            m_vertices_position.append(position);
            m_cube_face_num.append(2);
            //u = y; v = z
            position.setY((qreal)u / (qreal)(CSettings::details() - 1) * 2.0);
            position.setZ((qreal)v / (qreal)(CSettings::details() - 1) * 2.0);
            m_vertices_position.append(position);
            m_cube_face_num.append(3);

            position = QVector3D(1.0, 1.0, 1.0);
            //u = x; v = y
            position.setX(1 - ((qreal)u / (qreal)(CSettings::details() - 1) * 2.0));
            position.setY(1 - ((qreal)v / (qreal)(CSettings::details() - 1) * 2.0));
            m_vertices_position.append(position);
            m_cube_face_num.append(4);
            //u = x; v = z
            position.setX(1 - ((qreal)u / (qreal)(CSettings::details() - 1) * 2.0));
            position.setZ(1 - ((qreal)v / (qreal)(CSettings::details() - 1) * 2.0));
            m_vertices_position.append(position);
            m_cube_face_num.append(5);
            //u = y; v = z
            position.setY(1 - ((qreal)u / (qreal)(CSettings::details() - 1) * 2.0));
            position.setZ(1 - ((qreal)v / (qreal)(CSettings::details() - 1) * 2.0));
            m_vertices_position.append(position);
            m_cube_face_num.append(6);
        }
    }

    init(m_vertices_position, m_vert_tex_coords);

    QOpenGLBuffer faces_num_buffer(QOpenGLBuffer::VertexBuffer);
    faces_num_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vao.bind();
    if(faces_num_buffer.create()) {
        faces_num_buffer.bind();
        faces_num_buffer.allocate(m_cube_face_num.constData(), m_cube_face_num.size() * sizeof(int));
        m_shader_program.enableAttributeArray("cube_face_num");
        m_shader_program.setAttributeBuffer("cube_face_num", GL_INT, 0, 1);
    }
    else {
        //TODO: process this error
    }
    m_vao.release();
}

void CTerrainMesh::init() {
    int size = CUBE_FACES * CSettings::details() * CSettings::details();
    m_vertices_position.reserve(size);
    m_cube_face_num.reserve(size);
    m_vert_tex_coords.reserve(size);

    _create_sphere_faces();
    m_shader_program.setUniformValue("radius", m_sphere_radius);
    m_shader_program.setUniformValue("min_height", CSettings::min_height());
    m_shader_program.setUniformValue("max_height", CSettings::max_height());
    m_shader_program.setUniformValue("grid_dim", QVector2D(CSettings::details(), CSettings::details()));

    _load_textures();
}

QString CTerrainMesh::_filename() const {
    //TODO
}

void CTerrainMesh::_load_textures() {
    QOpenGLTexture heightmap_texture(m_heightmap->heightmap(), QOpenGLTexture::DontGenerateMipMaps);
    QOpenGLFunctions::glActiveTexture(heightmap_texture);
    m_shader_program.setUniformValue("heightmap", m_textures.size() + HEIGHTMAP_TEXTURE_OFFSET);
    heightmap_texture.bind();

    //TODO
}

int CTerrainMesh::seed() const {
    return m_heightmap->seed();
}

void CTerrainMesh::render() {
    m_cdlod_terrain->select_lod();
    for(int i = 0; i < CUBE_FACES; ++i) {
        QSharedPointer<CDLOD::CSelection> selection = m_cdlod_terrain->get_selection(i);
        //TODO
    }
    _load_textures();
}
