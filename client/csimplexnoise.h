#ifndef CSIMPLEXNOISE_H
#define CSIMPLEXNOISE_H

#define CUBE_EDGES 12
#define PERMUTATIONS 256
#define SIMPLEX_VERTICES 4
#define COORD_NUM 3

#include <random>
#include <cmath>

/*!
 * \brief The CSimplexNoise class
 * Simplex noise generator. Based on http://webstaff.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf.
 */
class CSimplexNoise {
private:
    static const int m_gradients[CUBE_EDGES][3] = {                       ///< The gradients are the midpoints of the vertices of a cube
        {1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0},
        {1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1},
        {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}
    };
    static int m_permutations[PERMUTATIONS << 1] = {                      ///< Permutation table. The same list is repeated twice
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
public:
    CSimplexNoise() {}
    /*!
     * \brief Initialize permutation table with new pseudorandom values
     * \param           seed            generator seed
     */
    static void init(int seed);
    /*!
     * \brief Produces raw 3D simplex noise
     * \param           xcoord          origin x-coordinate
     * \param           ycoord          origin y-coordinate
     * \param           zcoord          origin z-coordinate
     * \return                          raw 3D simplex noise value
     */
    static double raw_noise_3d(double xcoord, double ycoord, double zcoord);
    /*!
     * \brief 3D multi-octave simplex noise
     * \param           octaves         number of octaves
     * \param           persistence     persistence value (in [0;1] range)
     * \param           scale           noise scale
     * \param           xcoord          origin x-coordinate
     * \param           ycoord          origin y-coordinate
     * \param           zcoord          origin z-coordinate
     * \return                          multi-octave simplex noise value
     */
    static double octave_noise_3d(int octaves, double persistence, double scale, double xcoord, double ycoord, double zcoord);
    /*!
     * \brief 3D scaled multi-octave simplex noise
     * \param           octaves         number of octaves
     * \param           persistence     persistence value (in [0;1] range)
     * \param           scale           noise scale
     * \param           lo_bound        lower bound for the noise value
     * \param           hi_bound        higher bound for the noise value
     * \param           xcoord          origin x-coordinate
     * \param           ycoord          origin y-coordinate
     * \param           zcoord          origin z-coordinate
     * \return                          simplex noise value between lo_bound and hi_bound
     */
    static double scaled_octave_noise_3d(int octaves, double persistence, double scale, double lo_bound, double hi_bound,
                                        double xcoord, double ycoord, double zcoord);
};

#endif // CSIMPLEXNOISE_H
