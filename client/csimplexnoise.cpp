#include "csimplexnoise.h"

CSimplexNoise::CSimplexNoise() {
    m_permutations = {
            151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
            8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
            35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
            134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
            55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,
            18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,
            250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
            189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,
            172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,
            228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,
            107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
            138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,

            151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
            8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
            35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
            134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
            55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
            18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,
            250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
            189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,
            172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,
            228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,
            107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
            138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
        };
}

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
