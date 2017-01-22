#include "cterrainmeshchunk.h"

CTerrainMeshChunk::CTerrainMeshChunk(const QSharedPointer<QOpenGLShaderProgram>& shader_program,
                                     const QVector<QSharedPointer<QOpenGLTexture> >& textures,
                                     const QSharedPointer<CPlanetHeightmap>& heightmap)
    : CMesh(shader_program, textures) {
    m_heightmap = heightmap;
}

void CTerrainMeshChunk::_generate_grid(int x_vert, int y_vert, Math::ECubeFace cube_face) {
    QVector3D position;
    for(int u = 0; u < x_vert; ++u) {
        for(int v = 0; v < y_vert; ++v) {
            if(cube_face == Math::ECubeFace::XY_NEGATIVE) {
                position = QVector3D(-1.0, -1.0, -1.0);
                //u = x; v = y
                position.setX((qreal)u / (qreal)(CSettings::details() - 1) * 2.0);
                position.setY((qreal)v / (qreal)(CSettings::details() - 1) * 2.0);
                m_vertices_position.append(position);
            }
            else if(cube_face == Math::ECubeFace::XZ_NEGATIVE) {
                position = QVector3D(-1.0, -1.0, -1.0);
                //u = x; v = z
                position.setX((qreal)u / (qreal)(CSettings::details() - 1) * 2.0);
                position.setZ((qreal)v / (qreal)(CSettings::details() - 1) * 2.0);
                m_vertices_position.append(position);
            }
            else if(cube_face == Math::ECubeFace::YZ_NEGATIVE) {
                position = QVector3D(-1.0, -1.0, -1.0);
                //u = y; v = z
                position.setY((qreal)u / (qreal)(CSettings::details() - 1) * 2.0);
                position.setZ((qreal)v / (qreal)(CSettings::details() - 1) * 2.0);
                m_vertices_position.append(position);
            }
            else if(cube_face == Math::ECubeFace::XY_POSITIVE) {
                position = QVector3D(1.0, 1.0, 1.0);
                //u = x; v = y
                position.setX(1 - ((qreal)u / (qreal)(CSettings::details() - 1) * 2.0));
                position.setY(1 - ((qreal)v / (qreal)(CSettings::details() - 1) * 2.0));
                m_vertices_position.append(position);
            }
            else if(cube_face == Math::ECubeFace::XZ_POSITIVE) {
                position = QVector3D(1.0, 1.0, 1.0);
                //u = x; v = z
                position.setX(1 - ((qreal)u / (qreal)(CSettings::details() - 1) * 2.0));
                position.setZ(1 - ((qreal)v / (qreal)(CSettings::details() - 1) * 2.0));
                m_vertices_position.append(position);
            }
            else if(cube_face == Math::ECubeFace::YZ_POSITIVE) {
                position = QVector3D(1.0, 1.0, 1.0);
                //u = y; v = z
                position.setY(1 - ((qreal)u / (qreal)(CSettings::details() - 1) * 2.0));
                position.setZ(1 - ((qreal)v / (qreal)(CSettings::details() - 1) * 2.0));
                m_vertices_position.append(position);
            }
            //heightmap generation
            m_heightmap->set_pixel(u, v, cube_face);
        }
    }
}

bool CTerrainMeshChunk::create(int x_vert, int y_vert, Math::ECubeFace cube_face) {
    int size = CUBE_FACES * x_vert * y_vert;
    m_vertices_position.reserve(size);
    m_vert_tex_coords.reserve(size);

    _generate_grid(x_vert, y_vert, cube_face);
    init(m_vertices_position, m_vert_tex_coords);

    m_shader_program->setUniformValue("radius", m_sphere_radius);
    m_shader_program->setUniformValue("min_height", CSettings::min_height());
    m_shader_program->setUniformValue("max_height", CSettings::max_height());
    m_shader_program->setUniformValue("grid_dim", QVector2D(CSettings::details(), CSettings::details()));
}

void CTerrainMeshChunk::_load_textures() {
    QOpenGLTexture heightmap_texture(m_heightmap->heightmap(), QOpenGLTexture::DontGenerateMipMaps);
    QOpenGLFunctions::glActiveTexture(heightmap_texture);
    m_shader_program.setUniformValue("heightmap", m_textures.size() + HEIGHTMAP_TEXTURE_OFFSET);
    heightmap_texture.bind();

    //TODO
}

void CTerrainMeshChunk::render() {
    m_shader_program->setUniformValue("cube_face_num", (int)cube_face);
    _load_textures();
    CMesh::render();
}

QString CTerrainMeshChunk::error() const {
    return m_init_error;
}

void CTerrainMeshChunk::set_scale(float scale) {
    m_shader_program->setUniformValue("scale", scale);
}
