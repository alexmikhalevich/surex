#include "cterrain.h"

CTerrain::CTerrain(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<CSettings>& settings_ptr) {
    m_camera = camera_ptr;
    m_settings = settings_ptr;

    QImage height_map_img(settings_ptr->height_map());
    m_height_map = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(height_map_img));
    m_cdlod_terrain.reset(new CDLOD::CTerrain(camera_ptr, m_height_map, settings_ptr));
}

void CTerrain::render() {
    m_cdlod_terrain->select_lod();
    QSharedPointer<CDLOD::CSelection> cur_selection = m_cdlod_terrain->get_selection();
    //TODO
}
