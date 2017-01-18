#include "cplanetheightmap.h"

CPlanetHeightmap::CPlanetHeightmap(int seed, const QSharedPointer<CSettings>& settings,
                                   qreal height_min, qreal height_max) {
    m_seed = seed;
    m_noise_octaves = settings->noise_octaves();
    m_noise_persistence = settings->noise_persistence();
    m_noise_scale = m_settings->noise_scale();
    m_height_min = height_min;
    m_height_max = height_max;

    CSimplexNoise::init(m_seed);
}

CPlanetHeightmap::CPlanetHeightmap(const QString& path, const QSharedPointer<CSettings>& settings,
                                   qreal height_min, qreal height_max) {
    m_heightmap = QImage(path);
    m_noise_octaves = settings->noise_octaves();
    m_noise_persistence = settings->noise_persistence();
    m_noise_scale = m_settings->noise_scale();
    m_height_min = height_min;
    m_height_max = height_max;
}

void CPlanetHeightmap::generate(qreal planet_radius) {
    //TODO
}

QSize CPlanetHeightmap::size() const {
    return m_heightmap.size();
}

qreal CPlanetHeightmap::height(qreal polar_angle, qreal azimut_angle) const {
    if(m_heightmap.isNull()) {
        //TODO
    }
    else {
        qreal x = (azimut_angle / MAX_AZIMUT_ANGLE) * m_heightmap.width();
        qreal y = (polar_angle / MAX_POLAR_ANGLE) * m_heightmap.height();
        return _color_to_height(m_heightmap.pixelColor((int)x, (int)y));
    }
}

qreal CPlanetHeightmap::height(const QVector3D& position) const {
    if(m_heightmap.isNull()) {
        return CSimplexNoise::scaled_octave_noise_3d(m_noise_octaves, m_noise_persistence, m_noise_scale,
                                       m_height_min, m_height_max, position.x(), position.y(), position.z());
    }
    else {
        //TODO
    }
}

int CPlanetHeightmap::seed() const {
    return m_seed;
}

void CPlanetHeightmap::serialize(const QString& filename) {
    //TODO
}
