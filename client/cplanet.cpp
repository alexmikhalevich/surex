#include "cplanet.h"

CPlanet::CPlanet(const QSharedPointer<CCamera>& camera_ptr, const QVector<QSharedPointer<QOpenGLTexture> >& textures) {
    m_terrain_mesh.reset(new CTerrainMesh(textures, "shaders/planet.vert", "shaders/planet.frag"));
    m_camera = camera_ptr;
}

CPlanet::CPlanet(const QSharedPointer<CCamera>& camera_ptr, const QVector<QSharedPointer<QOpenGLTexture> >& textures, int seed) {
    m_terrain_mesh.reset(new CTerrainMesh(textures, "shaders/planet.vert", "shaders/planet.frag", seed));
    m_camera = camera_ptr;
}

void CPlanet::render() {

}

void CPlanet::serialize(const QString& filename) {
    //TODO
}
