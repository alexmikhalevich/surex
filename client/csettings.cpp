#include "csettings.h"

CSettings::CSettings() : m_samples_num(2) {
}

int CSettings::samples_num() const {
    return m_samples_num;
}

short CSettings::max_lod_level() const {
    return m_max_lod_level;
}

qreal CSettings::visibility_range(short level) const {
    if(level < m_visibility_ranges.size())
        return m_visibility_ranges.at(level);
}

int CSettings::max_selection_size() const {
    return m_max_selection_size;
}

qreal CSettings::lod_level_distance_ratio() const {
    return m_lod_level_distance_ratio;
}
