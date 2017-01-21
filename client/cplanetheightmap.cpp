#include "cplanetheightmap.h"

CPlanetHeightmap::CPlanetHeightmap(int seed, int size) {
    m_seed = seed;
    m_heightmap = QImage(size, size, QImage::Format_Indexed8);
    m_noise_octaves = settings->noise_octaves();
    m_noise_persistence = settings->noise_persistence();
    m_noise_scale = m_settings->noise_scale();
    m_height_min = settings->min_height();
    m_height_max = settings->max_height();

    CSimplexNoise::init(m_seed);
}

CPlanetHeightmap::CPlanetHeightmap(const QString& path) {
    m_heightmap = QImage(path);
    m_noise_octaves = settings->noise_octaves();
    m_noise_persistence = settings->noise_persistence();
    m_noise_scale = m_settings->noise_scale();
    m_height_min = settings->min_height();
    m_height_max = settings->max_height();
}

void CPlanetHeightmap::set_pixel(int x, int y) {
    //TODO: replace with 2D simplex noise
    int col = CSimplexNoise::scaled_octave_noise_3d(CSettings::noise_octaves(), CSettings::noise_persistence(),
                                                    CSettings::noise_scale(), 0, 255, x, y, 1);
    m_heightmap.setPixelColor(x, y, QColor(col, col, col));
}

QSize CPlanetHeightmap::size() const {
    return m_heightmap.size();
}

int CPlanetHeightmap::seed() const {
    return m_seed;
}

void CPlanetHeightmap::serialize(const QString& filename) {
    //TODO
}

QImage& CPlanetHeightmap::heightmap() {
    return m_heightmap;
}
