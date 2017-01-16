#ifndef CTERRAIN_H
#define CTERRAIN_H

#include <qt5/QtCore/QScopedPointer>
#include <qt5/QtCore/QSharedPointer>
#include <qt5/QtGui/QImage>
#include "CDLOD/cterrain.h"
#include "CDLOD/cselection.h"
#include "cmesh.h"
#include "irenderingobject.h"
#include "csettings.h"
#include "ccamera.h"

/*!
 * \brief The CTerrain class
 * Terrain representation for rendering
 */
class CTerrain : public IRenderingObject
{
private:
    QScopedPointer<CDLOD::CTerrain> m_cdlod_terrain;            ///< CDLOD algorithm
    QScopedPointer<CMesh> m_terrain_mesh;                       ///< Terrain mesh
    QSharedPointer<CSettings> m_settings;                       ///< CSettings instance which holds all system parameters
    QSharedPointer<CCamera> m_camera;                           ///< Camera object, necessary for the CDLOD algorithm
    QSharedPointer<QOpenGLTexture> m_height_map;                ///< Height map for generating our landscape
public:
    CTerrain(const QSharedPointer<CCamera>& camera_ptr, const QSharedPointer<CSettings>& settings_ptr);
    /*!
     * \brief Render terrain
     */
    virtual void render();
};

#endif // CTERRAIN_H
