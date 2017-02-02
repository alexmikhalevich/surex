#include "cplanet.h"

CPlanet::CPlanet(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<QOpenGLContext>& context, int seed) {
    _load_textures();

    m_shader_program = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);
    m_shader_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/planet.vert");
    m_shader_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/planet.frag");

    m_radius = qMin(rand() + CSettings::min_radius(), CSettings::max_radius());

    if(seed != 0)
        m_heightmap = QSharedPointer<CPlanetHeightmap>(new CPlanetHeightmap(seed, m_radius));
    else
        m_heightmap = QSharedPointer<CPlanetHeightmap>(new CPlanetHeightmap(""));     //TODO: path to file

    m_terrain_mesh.reset(new CTerrainMeshChunk(m_shader_program, m_textures, m_heightmap, context));
    for(int i = 0; i < CUBE_FACES; ++i) {
        bool res = m_terrain_mesh->create(static_cast<int>(m_radius / CSettings::min_radius()) * CSettings::details(),
                                          static_cast<int>(m_radius / CSettings::min_radius()) * CSettings::details(),
                                          static_cast<Math::ECubeFace>(i), m_radius);
        if(!res) {
            //TODO: process this error
        }
    }

    m_camera = camera_ptr;
}

void CPlanet::_load_textures() {
    //TODO: textures for CPlanet
}

void CPlanet::render() {
    m_terrain_mesh->render();
}

void CPlanet::serialize(const QString& filename) {
    //TODO: CPlanet serialization
}
