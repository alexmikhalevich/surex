#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <qt5/QtCore/QString>

class ISerializable {
public:
    virtual void serialize(const QString& filename) = 0;
};

#endif // ISERIALIZABLE_H
