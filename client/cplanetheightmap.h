#ifndef CPLANETHEIGHTMAP_H
#define CPLANETHEIGHTMAP_H

#include <qt5/QtGui/QImage>
#include <qt5/QtCore/QVector>
#include <qt5/QtGui/QColor>
#include "iserializable.h"
#include "csimplexnoise.h"
#include "csettings.h"
#include "utility.h"

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

public:
    CPlanetHeightmap(int seed, int size);
    CPlanetHeightmap(const QString& path);
    virtual ~CPlanetHeightmap() {}
    /*!
     * \brief Saves all current heightmap data
     * \param           filename            file which will contain the heilghtmap
     */
    virtual void serialize(const QString& filename);
    /*!
     * \brief Sets color of the particular pixel
     * \param       x       x-coordinate of the pixel
     * \param       y       y-coordinate of the pixel
     */
    void set_pixel(int x, int y, Math::ECubeFace face);
    /*!
     * \brief Returns heightmap size
     * \return          heightmap size
     */
    QSize size() const;
    /*!
     * \brief Returns seed which was used for simplex noise generation
     * \return          seed
     */
    int seed() const;
    /*!
     * \brief Returns reference to the heightmap
     * \return          reference to the heightmap
     */
    QImage& heightmap();
};

#endif // CPLANETHEIGHTMAP_H
