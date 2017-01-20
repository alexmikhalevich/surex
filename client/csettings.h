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
    static int m_samples_num;                                  ///< Number of samples per pixel when multisampling is enabled
    static int m_max_selection_size;                           ///< Maximum selection pool size
    static short m_max_lod_level;                              ///< Maximum LOD value
    static qreal m_lod_level_distance_ratio;                   ///< The number of times at which decreases rendering detail with increasing LOD
    static QVector<qreal> m_visibility_ranges;                 ///<
    static QSize m_details;                                    ///< The amount of vertices per one unit cube's edge (along x-axis and y-axis)
    static qreal m_noise_scale;                                ///< Simplex noise scale
    static qreal m_noise_persistence;                          ///< Simplex noise persistence
    static int m_noise_octaves;                                ///< Simplex noise octaves
    static double m_max_height;                                ///< Max terrain height
    static double m_min_height;                                ///< Min terrain height
public:
    CSettings();
    static int samples_num() const;
    static int max_selection_size() const;
    static short max_lod_level() const;
    static qreal visibility_range(short level) const;
    static qreal lod_level_distance_ratio() const;
    static QSize details() const;
    static double noise_scale() const;
    static double noise_persistence() const;
    static int noise_octaves() const;
    static double max_height() const;
    static double min_height() const;
};

#endif // CSETTINGS_H
