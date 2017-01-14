#include "csettings.h"

CSettings::CSettings() : m_samples_num(2) {
}

int CSettings::get_samples_num() const {
    return m_samples_num;
}

int CSettings::get_max_lod_level() const {
    return m_max_lod_level;
}
