#include "csettings.h"

CSettings::CSettings() {
    m_samples_num = 2;
}

int CSettings::samples_num() {
    return m_samples_num;
}

short CSettings::max_lod_level() {
    return m_max_lod_level;
}

qreal CSettings::visibility_range(short level) {
    if(level < m_visibility_ranges.size())
        return m_visibility_ranges.at(level);
}

int CSettings::max_selection_size() {
    return m_max_selection_size;
}

qreal CSettings::lod_level_distance_ratio() {
    return m_lod_level_distance_ratio;
}

int CSettings::details() {
    return m_details;
}

int CSettings::noise_octaves() {
    return m_noise_octaves;
}

double CSettings::noise_persistence() {
    return m_noise_persistence;
}

double CSettings::noise_scale() {
    return m_noise_scale;
}

float CSettings::max_height() {
    return m_max_height;
}

float CSettings::min_height() {
    return m_min_height;
}

int CSettings::min_radius() {
    return m_min_radius;
}

int CSettings::max_radius() {
    return m_max_radius;
}
