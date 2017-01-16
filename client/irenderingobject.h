#ifndef IRENDERINGOBJECT_H
#define IRENDERINGOBJECT_H

/*!
 * \brief The IRenderingObject class
 * Common interface for rendering objects
 */
class IRenderingObject
{
public:
    /*!
     * \brief Render object
     */
    virtual void render() = 0;
};

#endif // IRENDERINGOBJECT_H
