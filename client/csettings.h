#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <qt5/QtCore/QVector>
/*!
 * \brief The CSettings class
 * Keeps all system parameters
 */
class CSettings {
private:
    int m_samples_num;
    int m_max_selection_size;
    short m_max_lod_level;
    QVector<qreal> m_visibility_ranges;
public:
    CSettings();
    int samples_num() const;
    int max_selection_size() const;
    short max_lod_level() const;
    qreal visibility_range(short level) const;
};

#endif // CSETTINGS_H
