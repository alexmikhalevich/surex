#ifndef CPLANETHEIGHTMAP_H
#define CPLANETHEIGHTMAP_H

#include <qt5/QtGui/QImage>
#include <qt5/QtCore/QVector>
#include <qt5/QtGui/QColor>
#include "iserializable.h"
#include "csimplexnoise.h"
#include "csettings.h"

#define MAX_POLAR_ANGLE 180.0
#define MAX_AZIMUT_ANGLE 360.0

/*!
 * \brief The CPlanetHeightmap class
 * Heightmap representation
 */
class CPlanetHeightmap : public ISerializable {
private:
    qreal m_noise_persistence;              ///< Simplex noise persistence (in [0; 1] range)
    qreal m_noise_scale;                    ///< Simplex noise scale
    qreal m_noise_octaves;                  ///< The number of simplex noise octaves
    qreal m_height_min;                     ///< Minimum terrain height
    qreal m_height_max;                     ///< Maximum terrain height
    QImage m_heightmap;                     ///< Holds heightmap image
    int m_seed;                             ///< Seed, necessary for simplex noise generation algorithm

    /*!
     * \brief Maps the heightmap color to the height value
     * \param[in]       color
     * \return          height
     */
    qreal _color_to_height(const QColor& color) const;
public:
    CPlanetHeightmap(int seed, const QSharedPointer<CSettings>& settings);
    CPlanetHeightmap(const QString& path, const QSharedPointer<CSettings>& settings);
    /*!
     * \brief Saves all current heightmap data
     * \param           filename            file which will contain the heilghtmap
     */
    virtual void serialize(const QString& filename);
    /*!
     * \brief Generate heightmap for the particular planet radius
     * \param[in]       planet_radius
     */
    void generate(qreal planet_radius);
    /*!
     * \brief Returns heightmap size
     * \return          heightmap size
     */
    QSize size() const;
    /*!
     * \brief Calculates height for the particular point on the sphere
     * \param[in]       polar_angle
     * \param[in]       azimut_angle
     * \return          height
     */
    qreal height(qreal polar_angle, qreal azimut_angle) const;
    /*!
     * \brief Calculates height for the particular point on the sphere
     * \param[in]       position        cartesian coordinates of the processed point
     * \return
     */
    qreal height(const QVector3D& position) const;
    /*!
     * \brief Returns seed which was used for simplex noise generation
     * \return          seed
     */
    int seed() const;
};

#endif // CPLANETHEIGHTMAP_H
