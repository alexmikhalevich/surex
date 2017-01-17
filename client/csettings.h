#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <qt5/QtCore/QVector>
#include <qt5/QtCore/QSize>

/*!
 * \brief The CSettings class
 * Keeps all system parameters
 */
class CSettings {
private:
    int m_samples_num;                                  ///< Number of samples per pixel when multisampling is enabled
    int m_max_selection_size;                           ///< Maximum selection pool size
    short m_max_lod_level;                              ///< Maximum LOD value
    qreal m_lod_level_distance_ratio;                   ///< The number of times at which decreases rendering detail with increasing LOD
    QVector<qreal> m_visibility_ranges;                 ///<
    QSize m_details;                                    ///< The amount of vertices per one unit cube's edge (along x-axis and y-axis)
public:
    CSettings();
    int samples_num() const;
    int max_selection_size() const;
    short max_lod_level() const;
    qreal visibility_range(short level) const;
    qreal lod_level_distance_ratio() const;
    QSize details() const;
};

#endif // CSETTINGS_H
