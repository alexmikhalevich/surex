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
    static int m_details;                                      ///< The minimum amount of vertices per one unit cube's edge
    static qreal m_noise_scale;                                ///< Simplex noise scale
    static qreal m_noise_persistence;                          ///< Simplex noise persistence
    static int m_noise_octaves;                                ///< Simplex noise octaves
    static float m_max_height;                                 ///< Max terrain height
    static float m_min_height;                                 ///< Min terrain height
    static int m_min_radius;                                   ///< Min planet radius
    static int m_max_radius;                                   ///< Max planet radius
public:
    CSettings();
    static int samples_num();
    static int max_selection_size();
    static short max_lod_level();
    static qreal visibility_range(short level);
    static qreal lod_level_distance_ratio();
    static int details();
    static double noise_scale();
    static double noise_persistence();
    static int noise_octaves();
    static float max_height();
    static float min_height();
    static int min_radius();
    static int max_radius();
};

#endif // CSETTINGS_H
