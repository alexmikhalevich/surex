#ifndef CPLANET_H
#define CPLANET_H

#include <qt5/QtCore/QScopedPointer>
#include <qt5/QtCore/QSharedPointer>
#include <qt5/QtGui/QImage>
#include "CDLOD/cterrain.h"
#include "CDLOD/cselection.h"
#include "cterrainmeshchunk.h"
#include "irenderable.h"
#include "csettings.h"
#include "ccamera.h"
#include "cplanetheightmap.h"

/*!
 * \brief The CPlanet class
 * Planet representation for rendering
 */
class CPlanet : public IRenderable, public ISerializable
{
private:
    QScopedPointer<CTerrainMeshChunk> m_terrain_mesh;                 ///< Terrain mesh
    QSharedPointer<CCamera> m_camera;                                 ///< Camera object, necessary for the CDLOD algorithm
    QOpenGLShaderProgram m_shader_program;
    QVector<QSharedPointer<QOpenGLTexture>> m_textures;               ///< Planet textures
    QSharedPointer<CPlanetHeightmap> m_heightmap;
    qreal m_radius;                                                   ///< Planet radius

    void _load_textures();
public:
    CPlanet(const QSharedPointer<CCamera>& camera_ptr, int seed = 0);
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
