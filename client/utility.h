#ifndef UTILITY_H
#define UTILITY_H

#include <qt5/QtGui/QVector3D>
#include <qt5/QtGui/QMatrix4x4>

namespace Math {
    class CPlane {
    private:
        QVector3D m_normal;
        qreal m_distance;
    public:
        CPlane() : m_normal(QVector3D(0.0, 0.0, 0.0)), m_distance(QVector3D(0.0, 0.0, 0.0)) {}
        CPlane(const QVector3D& normal, const QVector3D distance) : m_normal(normal), m_distance(distance) {}
        ~CPlane() {}
        void set_normal(const QVector3D& normal);
        void set_distance(qreal distance);
        qreal distance(const QVector3D& point) const;
        bool front_facing(const QVector3D& direction) const;
    };

    class CBoundingBox {
    private:
        QVector3D m_center;
        QVector3D m_half_size;
    public:
        CBoundingBox() : m_center(QVector3D(0.0, 0.0, 0.0)), m_half_size(QVector3D(0.0, 0.0, 0.0)) {}
        CBoundingBox(const QVector3D& center, const QVector3D& half_size) : m_center(center), m_half_size(half_size) {}
        ~CBoundingBox() {}
        void get_min(QVector3D& result) const;
        void get_max(QVector3D& result) const;
        qreal min_distance_squared(const QVector3D& point) const;
        qreal max_distance_squared(const QVector3D& point) const;
        void vertex_positive(const QVector3D& normal, QVector3D& result) const;
        void vertex_negative(const QVector3D& normal, QVector3D& result) const;
        QVector3D center() const;
        QVector3D half_size() const;
    };

    class CBoundingFrustum {
    private:
        CPlane m_planes[6];
    public:
        CBoundingFrustum() {}
        CBoundingFrustum(const QMatrix4x4& modelviewproj);
        void from_matrix(const QMatrix4x4& modelviewproj);
    };

    class CBoundingSphere {
    private:
        QVector3D m_center;
        qreal m_radius;
    public:
        CBoundingSphere() : m_center(QVector3D(0.0, 0.0, 0.0)), m_radius(0.0) {}
        CBoundingSphere(const QVector3D& center, qreal radius) : m_center(center), m_radius(radius) {}
        ~CBoundingSphere() {}
    };

    class CCollision {
        enum ECollisionType {
            CONTAINS,
            INTERSECTS,
            NONE
        };
        static inline ECollisionType contains(const CBoundingBox& box_1, const CBoundingBox& box_2);
        static inline ECollisionType contains(const CBoundingBox& box, const CBoundingFrustum& frustrum);
        static inline bool intersects(const CBoundingBox& box, const CBoundingSphere& sphere);
    };
}
#endif // UTILITY_H
