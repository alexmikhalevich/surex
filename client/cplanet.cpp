#include "cplanet.h"

CPlanet::CTerrain(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<CSettings>& settings_ptr,
                   const QSharedPointer<CPlanetHeightmap>& heightmap) {
    m_camera = camera_ptr;
    m_settings = settings_ptr;

    QImage height_map_img(settings_ptr->height_map());
    m_height_map = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(height_map_img));
    m_cdlod_terrain.reset(new CDLOD::CTerrain(camera_ptr, m_height_map, settings_ptr));
}

void CPlanet::_map_cube_to_sphere(QVector3D& point) const {
    qreal x2 = point.x() * point.x();
    qreal y2 = point.y() * point.y();
    qreal z2 = point.z() * point.z();

    //using Philip Nowell's formula from here http://mathproofs.blogspot.ru/2005/07/mapping-cube-to-sphere.html
    point.setX(point.x() * qSqrt(1.0 - (y2 * 0.5) - (z2 * 0.5) + ((y2 * z2) / 3.0)));
    point.setY(point.y() * qSqrt(1.0 - (z2 * 0.5) - (x2 * 0.5) + ((x2 * z2) / 3.0)));
    point.setZ(point.z() * qSqrt(1.0 - (x2 * 0.5) - (y2 * 0.5) + ((y2 * x2) / 3.0)));
}

void CPlanet::_create_sphere_faces() {
    QVector3D min_position(-1.0f, -1.0, -1.0);
    for(int x = 0; x < m_settings->details().width(); ++x) {
        for(int y = 0; y < m_settings->details().height(); ++y) {
            QVector3D position = min_position;
            position.setX((qreal)x / (qreal)(m_settings->details().width() - 1) * 2.0);
            position.setY((qreal)y / (qreal)(m_settings->details().height() - 1) * 2.0);
            _map_cube_to_sphere(position);
            QVector3D normal = position.normalized();
            position *= m_radius;
            m_vertices_position.append(CMesh::SVertexPosition(position));
            m_vertices_normal.append(CMesh::SVertexNormal(normal));
        }
    }
}

void CPlanet::render() {
    m_cdlod_terrain->select_lod();
    QSharedPointer<CDLOD::CSelection> cur_selection = m_cdlod_terrain->get_selection();
    //TODO
}
