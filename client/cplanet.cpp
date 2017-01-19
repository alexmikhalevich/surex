#include "cplanet.h"

CPlanet::CPlanet(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<CSettings>& settings_ptr) {
    _init(camera_ptr, settings_ptr);
    m_heightmap = QSharedPointer<CPlanetHeightmap>(new CPlanetHeightmap(_filename(), settings_ptr));
    m_seed = m_heightmap.seed();
    _post_init();
}

CPlanet::CPlanet(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<CSettings>& settings_ptr, int seed) {
    _init(camera_ptr, settings_ptr);
    m_seed = seed;
    m_heightmap = QSharedPointer<CPlanetHeightmap>(new CPlanetHeightmap(m_seed, settings_ptr));
    _post_init();
}

void CPlanet::_init(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<CSettings>& settings_ptr) {
    m_camera = camera_ptr;
    m_settings = settings_ptr;

    int size = CUBE_FACES * m_settings->details().width() * m_settings->details().height();
    m_vertices_position.resize(size);
    m_vertices_normal.resize(size);
    m_vert_tex_coords.resize(size);

    m_cdlod_terrain.reset(new CDLOD::CTerrain(camera_ptr, m_heightmap, settings_ptr));
    _load_textures();
    m_terrain_mesh.reset(new CMesh(m_textures, "shaders/planet.vert", "shaders/planet.frag"));
    if(!m_terrain_mesh->create_successfull()) {
        //TODO: process this error
    }
}

void CPlanet::_post_init() {
    _create_sphere_faces();
    m_terrain_mesh->init(m_vertices_position, m_vertices_normal, m_vert_tex_coords/*, m_indices*/);
}

QString CPlanet::_filename() const {
    //TODO
}

void CPlanet::_load_textures() {
    //TODO
}

void CPlanet::_map_cube_to_sphere(QVector3D& point) const {
    qreal x2 = point.x() * point.x();
    qreal y2 = point.y() * point.y();
    qreal z2 = point.z() * point.z();

    //using Philip Nowell's formula from here: http://mathproofs.blogspot.ru/2005/07/mapping-cube-to-sphere.html
    point.setX(point.x() * qSqrt(1.0 - (y2 * 0.5) - (z2 * 0.5) + ((y2 * z2) / 3.0)));
    point.setY(point.y() * qSqrt(1.0 - (z2 * 0.5) - (x2 * 0.5) + ((x2 * z2) / 3.0)));
    point.setZ(point.z() * qSqrt(1.0 - (x2 * 0.5) - (y2 * 0.5) + ((y2 * x2) / 3.0)));
}

void CPlanet::_create_sphere_faces() {
    QVector3D min_position[6] = {
        QVector(-1.0, -1.0, -1.0)
    };
    int width = m_settings->details().width();
    int height = m_settings->details().height();
    for(int i = 0; i < CUBE_FACES; ++i) {
        for(int x = 0; x < width; ++x) {
            for(int y = 0; y < height; ++y) {
                QVector3D position = min_position;
                position.setX((qreal)x / (qreal)(m_settings->details().width() - 1) * 2.0);
                position.setY((qreal)y / (qreal)(m_settings->details().height() - 1) * 2.0);
                _map_cube_to_sphere(position);
                QVector3D normal = position.normalized();
                position *= m_radius;
                position += normal * m_heightmap->height(position);
                m_vertices_position[i * (x * height + y)] = CMesh::SVertexPosition(position);
                m_vertices_normal[i * (x * height + y)] = CMesh::SVertexNormal(normal);
            }
        }
    }
}

void CPlanet::render() {
    //m_cdlod_terrain->select_lod();
    //QSharedPointer<CDLOD::CSelection> cur_selection = m_cdlod_terrain->get_selection();

}

void CPlanet::serialize(const QString& filename) {
    //TODO
}
