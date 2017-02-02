#include "cterrainmeshchunk.h"

CTerrainMeshChunk::CTerrainMeshChunk(const QSharedPointer<QOpenGLShaderProgram>& shader_program,
                                     const QVector<QSharedPointer<QOpenGLTexture> >& textures,
                                     const QSharedPointer<CPlanetHeightmap>& heightmap,
                                     const QSharedPointer<QOpenGLContext>& context)
    : CMesh(shader_program, textures, context) {
    m_heightmap = heightmap;
    m_context = context;
}

void CTerrainMeshChunk::_generate_grid(int x_vert, int y_vert, Math::ECubeFace cube_face) {
    QVector3D position;
    for(int u = 0; u < x_vert; ++u) {
        for(int v = 0; v < y_vert; ++v) {
            if(cube_face == Math::ECubeFace::XY_NEGATIVE) {
                position = QVector3D(-1.0, -1.0, -1.0);
                //u = x; v = y
                position.setX(static_cast<float>(u / (CSettings::details() - 1) * 2.0));
                position.setY(static_cast<float>(v / (CSettings::details() - 1) * 2.0));
                m_vertices_position.append(position);
            }
            else if(cube_face == Math::ECubeFace::XZ_NEGATIVE) {
                position = QVector3D(-1.0, -1.0, -1.0);
                //u = x; v = z
                position.setX(static_cast<float>(u / (CSettings::details() - 1) * 2.0));
                position.setZ(static_cast<float>(v / (CSettings::details() - 1) * 2.0));
                m_vertices_position.append(position);
            }
            else if(cube_face == Math::ECubeFace::YZ_NEGATIVE) {
                position = QVector3D(-1.0, -1.0, -1.0);
                //u = y; v = z
                position.setY(static_cast<float>(u / (CSettings::details() - 1) * 2.0));
                position.setZ(static_cast<float>(v / (CSettings::details() - 1) * 2.0));
                m_vertices_position.append(position);
            }
            else if(cube_face == Math::ECubeFace::XY_POSITIVE) {
                position = QVector3D(1.0, 1.0, 1.0);
                //u = x; v = y
                position.setX(1 - static_cast<float>(u / (CSettings::details() - 1) * 2.0));
                position.setY(1 - static_cast<float>(v / (CSettings::details() - 1) * 2.0));
                m_vertices_position.append(position);
            }
            else if(cube_face == Math::ECubeFace::XZ_POSITIVE) {
                position = QVector3D(1.0, 1.0, 1.0);
                //u = x; v = z
                position.setX(1 - static_cast<float>(u / (CSettings::details() - 1) * 2.0));
                position.setZ(1 - static_cast<float>(v / (CSettings::details() - 1) * 2.0));
                m_vertices_position.append(position);
            }
            else if(cube_face == Math::ECubeFace::YZ_POSITIVE) {
                position = QVector3D(1.0, 1.0, 1.0);
                //u = y; v = z
                position.setY(1 - static_cast<float>(u / (CSettings::details() - 1) * 2.0));
                position.setZ(1 - static_cast<float>(v / (CSettings::details() - 1) * 2.0));
                m_vertices_position.append(position);
            }
            //heightmap generation
            m_heightmap->set_pixel(u, v, cube_face);
        }
    }
}

bool CTerrainMeshChunk::create(int x_vert, int y_vert, Math::ECubeFace cube_face, int radius) {
    int size = CUBE_FACES * x_vert * y_vert;
    m_vertices_position.reserve(size);
    m_vert_tex_coords.reserve(size);

    _generate_grid(x_vert, y_vert, cube_face);
    bool res = init(m_vertices_position, m_vert_tex_coords);

    m_shader_program->setUniformValue("radius", radius);
    m_shader_program->setUniformValue("min_height", CSettings::min_height());
    m_shader_program->setUniformValue("max_height", CSettings::max_height());
    m_shader_program->setUniformValue("grid_dim", QVector2D(CSettings::details(), CSettings::details()));

    return res;
}

void CTerrainMeshChunk::_load_textures() {
    QOpenGLTexture heightmap_texture(m_heightmap->heightmap(), QOpenGLTexture::DontGenerateMipMaps);
    QOpenGLFunctions opengl_funcs(m_context.data());
    opengl_funcs.glActiveTexture(heightmap_texture.textureId());
    m_shader_program->setUniformValue("heightmap", m_textures.size() + HEIGHTMAP_TEXTURE_OFFSET);
    heightmap_texture.bind();

    //TODO: textures for CTerrainMeshChunk
}

void CTerrainMeshChunk::render() {
    m_shader_program->setUniformValue("cube_face_num", m_face);
    _load_textures();
    CMesh::render();
}

QString CTerrainMeshChunk::error() const {
    return m_init_error;
}

void CTerrainMeshChunk::set_scale(float scale) {
    m_shader_program->setUniformValue("scale", scale);
}
