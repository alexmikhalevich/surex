#ifndef IRENDERINGOBJECT_H
#define IRENDERINGOBJECT_H

/*!
 * \brief The IRenderable class
 * Common interface for renderable objects
 */
class IRenderable
{
public:
    /*!
     * \brief Render object
     */
    virtual void render() = 0;
};

#endif // IRENDERINGOBJECT_H
