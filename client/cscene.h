#ifndef CSCENE_H
#define CSCENE_H

#include <qt5/QtCore/QVector>
#include <qt5/QtCore/QSharedPointer>
#include "irenderingobject.h"

/*!
 * \brief The CScene class
 * Current scene representation
 */
class CScene
{
private:
    QVector<QSharedPointer<IRenderingObject>> m_objects;                       ///< Scene objects
public:
    CScene();
    /*!
     * \brief Add object to the scene
     * \param           object            object which will be added to the scene
     */
    void add_object(const QSharedPointer<IRenderingObject>& object);
    /*!
     * \brief Render current scene
     */
    void render();
};

#endif // CSCENE_H
