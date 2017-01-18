#include "csimplexnoise.h"

void CSimplexNoise::init(int seed) {
    std::srand(seed);
    for(int i = 0; i < PERMUTATIONS; ++i) {
        int k = m_permutations[i];
        int j = rand() % PERMUTATIONS;
        m_permutations[i] = m_permutations[j];
        m_permutations[j] = k;

        m_permutations[PERMUTATIONS + i] = m_permutations[j];
        m_permutations[PERMUTATIONS + j] = k;
    }
}

//TODO: optimize
double CSimplexNoise::raw_noise_3d(double xcoord, double ycoord, double zcoord) {
    double noise[SIMPLEX_VERTICES];
    double contribution[SIMPLEX_VERTICES];
    double offsets[SIMPLEX_VERTICES][COORD_NUM];
    double skewed_point[COORD_NUM];
    double unskewed_point[COORD_NUM];
    double second_corner[COORD_NUM];
    double third_corner[COORD_NUM];
    int hashed_skewed[COORD_NUM];
    double coords[COORD_NUM] = {
        xcoord,
        ycoord,
        zcoord
    };

    double skew_factor = (xcoord + ycoord + zcoord) / 3.0;
    for(int i = 0; i < COORD_NUM; ++i)
        skewed_point[i] = std::floor(coords[i] + skew_factor);

    double unskew_factor = (skewed_point[0] + skewed_point[1] + skewed_point[2]) / 6.0;
    for(int i = 0; i < COORD_NUM; ++i) {
        unskewed_point[i] = skewed_point[i] - unskew_factor;
        offsets[0][i] = coords[i] - unskewed_point[i];
    }

    if(offsets[0][0] >= offsets[0][1]) {
        if(offsets[0][1] >= offsets[0][2]) {
            second_corner = { 1, 0, 0 };
            third_corner = { 1, 1, 0 };
        }
        else if(offsets[0][0] >= offsets[0][2]) {
            second_corner = { 1, 0, 0 };
            third_corner = { 1, 0, 1 };
        }
        else {
            second_corner = { 0, 0, 1 };
            third_corner = { 1, 0, 1 };
        }
    }
    if(offsets[0][0] < offsets[0][1]) {
        if(offsets[0][1] < offsets[0][2]) {
            second_corner = { 0, 0, 1 };
            third_corner = { 0, 1, 1 };
        }
        else if(offsets[0][0] < offsets[0][2]) {
            second_corner = { 0, 1, 0};
            third_corner = { 0, 1, 1 };
        }
        else {
            second_corner = { 0, 1, 0 };
            third_corner = { 1, 1, 0 };
        }
    }

    for(int i = 0; i < COORD_NUM; ++i) {
        offsets[1][i] = offsets[0][i] - second_corner[i] + 1/6;
        offsets[2][i] = offsets[0][i] - third_corner[i] + 1/3;
        offsets[3][i] = offsets[0][i] - 0.5;

        hashed_skewed = skewed_point[i] & 255;
    }

    int gradient_indices[SIMPLEX_VERTICES] = {
        m_permutations[hashed_skewed[0] + m_permutations[hashed_skewed[1] + m_permutations[hashed_skewed[2]]]] % 12,
        m_permutations[hashed_skewed[0] + second_corner[0] + m_permutations[hashed_skewed[1] + second_corner[1]
            + m_permutations[hashed_skewed[2] + second_corner[2]]]] % 12,
        m_permutations[hashed_skewed[0] + third_corner[0] + m_permutations[hashed_skewed[1] + third_corner[1]
            + m_permutations[hashed_skewed[2] + third_corner[2]]]] % 12,
        m_permutations[hashed_skewed[0] + 1 + m_permutations[hashed_skewed[1] + 1 + m_permutations[hashed_skewed[2] + 1]]] % 12
    };

    for(int i = 0; i < SIMPLEX_VERTICES; ++i) {
        contribution[i] = 0.6 - offsets[i][0] * offsets[i][0] - offsets[i][1] * offsets[i][1] - offsets[i][2] * offsets[i][2];
        if(contribution[i] < 0) noise[i] = 0.0;
        else {
            contribution[i] *= contribution[i];
            noise[i] = contribution[i] * contribution[i] * (m_gradients[gradient_indices[i]][0] * offsets[i][0]
                                                          + m_gradients[gradient_indices[i]][1] * offsets[i][1]
                                                          + m_gradients[gradient_indices[i]][2] * offsets[i][2]);
        }
    }

    return 32.0 * (noise[0] + noise[1] + noise[2] + noise[3]);
}

double CSimplexNoise::octave_noise_3d(int octaves, double persistence, double scale, double xcoord, double ycoord, double zcoord) {
    double total = 0.0;
    double frequency = scale;
    double amplitude = 1.0;
    double max_amplitude = 0.0;

    for(int i = 0; i < octaves; ++i) {
        total += raw_noise_3d(xcoord, ycoord, zcoord) * amplitude;
        frequency *= 2;
        max_amplitude += amplitude;
        amplitude *= persistence;
    }

    return total / max_amplitude;
}

double CSimplexNoise::scaled_octave_noise_3d(int octaves, double persistence, double scale, double lo_bound, double hi_bound,
                                             double xcoord, double ycoord, double zcoord) {
    return octave_noise_3d(octaves, persistence, scale, xcoord, ycoord, zcoord) * (hi_bound- lo_bound) / 2 + (hi_bound + lo_bound) / 2;
}
