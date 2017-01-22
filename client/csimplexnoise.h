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
    static constexpr int m_gradients[CUBE_EDGES][3] = {                   ///< The gradients are the midpoints of the vertices of a cube
        {1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0},
        {1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1},
        {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}
    };
    static int m_permutations[PERMUTATIONS << 1];                         ///< Permutation table. The same list is repeated twice
public:
    CSimplexNoise();
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
