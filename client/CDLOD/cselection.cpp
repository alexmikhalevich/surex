#include "cselection.h"

using namespace CDLOD;

CSelection::CSelection() {
}

const QVector3D& CSelection::observer_position() const {

}

qreal CSelection::visibiliry_range(short level) const {
    return m_settings->visibility_range(level);
}

short CSelection::max_lod_level() const {
    return m_settings->max_lod_level();
}

int CSelection::selection_size() const {
    return m_selection.size();
}

int CSelection::max_selection_size() const {
    return m_settings->max_selection_size();
}

void CSelection::push_node(QSharedPointer<CQuadtreeNode>& node_ptr) {
    m_selection.push_back(node_ptr);
}

QSharedPointer<CSettings> CSelection::settings() {
    return m_settings;
}

void CSelection::set_small_visible_distance(bool value) {
    m_small_visible_distance = value;
}

qreal CSelection::morph_start(short level) {

}
