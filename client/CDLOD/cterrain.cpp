#include "cterrain.h"

using namespace CDLOD;

CTerrain::CTerrain(QSharedPointer<CCamera>& camera, QSharedPointer<CSettings>& settings) {
    m_selection = QSharedPointer<CSelection>(new CSelection(camera, settings));
    //m_settings = settings;

    m_quadtree.reset(new CQuadtree(m_selection));
    m_quadtree->init(settings);
}

void CTerrain::select_lod() {
    m_quadtree->select();
}

QSharedPointer<CSelection> CTerrain::get_selection() {
    return m_selection;
}
