#ifndef CPLANET_H
#define CPLANET_H

#include <qt5/QtCore/QScopedPointer>
#include <qt5/QtCore/QSharedPointer>
#include <qt5/QtGui/QImage>
#include "CDLOD/cterrain.h"
#include "CDLOD/cselection.h"
#include "cmesh.h"
#include "irenderingobject.h"
#include "csettings.h"
#include "ccamera.h"
#include "cplanetheightmap.h"

#define CUBE_FACES 6

/*!
 * \brief The CPlanet class
 * Planet representation for rendering
 */
class CPlanet : public IRenderingObject, public ISerializable
{
private:
    QScopedPointer<CDLOD::CTerrain> m_cdlod_terrain;                  ///< CDLOD algorithm
    QScopedPointer<CMesh> m_terrain_mesh;                             ///< Terrain mesh
    QSharedPointer<CSettings> m_settings;                             ///< CSettings instance which holds all system parameters
    QSharedPointer<CCamera> m_camera;                                 ///< Camera object, necessary for the CDLOD algorithm
    QSharedPointer<CPlanetHeightmap> m_heightmap;                     ///< Height map for generating our landscape
    QVector<CMesh::SVertexPosition> m_vertices_position;              ///< Vertex buffer for rendering
    QVector<CMesh::SVertexNormal> m_vertices_normal;                  ///< Normal buffer for rendering
    QVector<CMesh::SVertexTextureCoords> m_vert_tex_coords;           ///< Texture coordinates buffer for rendering
//    QVector<unsigned int> m_indices;                                  ///< Index buffer
    QVector<QSharedPointer<QOpenGLTexture>> m_textures;               ///< Planet textures
    qreal m_radius;                                                   ///< Planet radius
    int m_seed;                                                       ///< Planet seed, necessary for simplex noise generation algorithm

    /*!
     * \brief Maps point on the unit cube to the sphere
     * \param           point                  mapped point
     */
    void _map_cube_to_sphere(QVector3D& point) const;
    /*!
     * \brief Maps unit cube's face to the part of the sphere
     */
    void _create_sphere_faces();
    /*!
     * \brief Does all necessary stuff for initialisation, common for both constuctors
     * \param           camera_ptr              camera object
     * \param           settings_ptr            all system settings
     */
    void _init(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<CSettings>& settings_ptr);
    /*!
     * \brief Post init stuff, common for both constructors
     */
    void _post_init();
    /*!
     * \brief Obtains the heightmap filename
     * \return          filename
     */
    QString _filename() const;
    /*!
     * \brief Creates planet textures
     */
    void _load_textures();
public:
    CPlanet(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<CSettings>& settings_ptr);
    CPlanet(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<CSettings>& settings_ptr, int seed);
    /*!
     * \brief Render planet
     */
    virtual void render();
    /*!
     * \brief Saves all current heightmap data
     * \param           filename            file which will contain the heilghtmap
     */
    virtual void serialize(const QString& filename);
};

#endif // CTERRAIN_H
