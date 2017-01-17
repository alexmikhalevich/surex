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

/*!
 * \brief The CPlanet class
 * Planet representation for rendering
 */
class CPlanet : public IRenderingObject
{
private:
    QScopedPointer<CDLOD::CTerrain> m_cdlod_terrain;            ///< CDLOD algorithm
    QScopedPointer<CMesh> m_terrain_mesh;                       ///< Terrain mesh
    QSharedPointer<CSettings> m_settings;                       ///< CSettings instance which holds all system parameters
    QSharedPointer<CCamera> m_camera;                           ///< Camera object, necessary for the CDLOD algorithm
    QSharedPointer<CPlanetHeightmap> m_height_map;              ///< Height map for generating our landscape
    QVector<CMesh::SVertexPosition> m_vertices_position;        ///< Vertex buffer for rendering
    QVector<CMesh::SVertexNormal> m_vertices_normal;            ///< Normal buffer for rendering
    QVector<CMesh::SVertexTextureCoords> m_vert_tex_coords;     ///< Texture coordinates buffer for rendering
    qreal m_radius;                                             ///< Planet radius

    /*!
     * \brief Maps point on the unit cube to the sphere
     * \param           point                  mapped point
     */
    void _map_cube_to_sphere(QVector3D& point) const;
    /*!
     * \brief Maps unit cube's face to the part of the sphere
     */
    void _create_sphere_faces();
public:
    CPlanet(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<CSettings>& settings_ptr,
             const QSharedPointer<CPlanetHeightmap>& heightmap);
    /*!
     * \brief Render planet
     */
    virtual void render();
};

#endif // CTERRAIN_H
