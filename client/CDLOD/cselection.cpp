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
    return m_size;
}

int CSelection::max_selection_size() const {
    return m_settings->max_selection_size();
}
