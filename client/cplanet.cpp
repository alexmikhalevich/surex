#include "cplanet.h"

CPlanet::CPlanet(const QSharedPointer<CCamera>& camera_ptr, int seed = 0) {
    _load_textures();

    m_shader_program.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/planet.vert");
    m_shader_program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/planet.frag");

    m_radius = qMin(rand() + CSettings::min_radius(), CSettings::max_radius());

    if(seed != 0)
        m_heightmap = QSharedPointer(new CPlanetHeightmap(seed, size));
    else
        m_heightmap = new QSharedPointer(new CPlanetHeightmap(""));     //TODO: path to file

    m_terrain_mesh.reset(new CTerrainMeshChunk(m_shader_program, m_textures, m_heightmap));
    for(int i = 0; i < CUBE_FACES; ++i)
        m_terrain_mesh->create((m_radius / CSettings::min_radius()) * CSettings::details(),
                               (m_radius / CSettings::min_radius()) * CSettings::details(), i);

    m_camera = camera_ptr;
}

void CPlanet::_load_textures() {
    //TODO
}

void CPlanet::render() {
    m_terrain_mesh->render();
}

void CPlanet::serialize(const QString& filename) {
    //TODO
}
