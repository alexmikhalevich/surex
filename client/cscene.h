#ifndef CSCENE_H
#define CSCENE_H

#include <qt5/QtCore/QVector>
#include <qt5/QtCore/QSharedPointer>
#include "irenderable.h"
#include "ccamera.h"

/*!
 * \brief The CScene class
 * Current scene representation
 */
class CScene
{
private:
    QVector<QSharedPointer<IRenderable>> m_objects;                       ///< Scene objects
    QSharedPointer<CCamera> m_camera;                                     ///< Camera object
public:
    CScene();
    ~CScene();
    /*!
     * \brief Add camera to the scene
     * \param[in]       position          camera position
     */
    void set_camera(const QVector3D& position);
    /*!
     * \brief Returns pointer to the camera object
     * \return          camera
     */
    QSharedPointer<CCamera> camera();
    /*!
     * \brief Add object to the scene
     * \param           object            object which will be added to the scene
     */
    void add_object(const QSharedPointer<IRenderable>& object);
    /*!
     * \brief Render current scene
     */
    void render();
};

#endif // CSCENE_H
