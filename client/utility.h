#ifndef UTILITY_H
#define UTILITY_H

#include <qt5/QtGui/QVector3D>
#include <qt5/QtGui/QMatrix4x4>

namespace Math {
    /*!
     * \brief The ECubeFace enum
     * Represents the unity cube faces
     */
    enum ECubeFace {
        XY_NEGATIVE = 0,
        XZ_NEGATIVE = 1,
        YZ_NEGATIVE = 2,
        XY_POSITIVE = 3,
        XZ_POSITIVE = 4,
        YZ_POSITIVE = 5
    };

    class CPlane {
    private:
        QVector3D m_normal;
        qreal m_distance;
    public:
        CPlane() : m_normal(QVector3D(0.0, 0.0, 0.0)), m_distance(0.0) {}
        CPlane(const QVector3D& normal, qreal distance) : m_normal(normal), m_distance(distance) {}
        ~CPlane() {}
        void set_normal(const QVector3D& normal);
        void set_distance(qreal distance);
        qreal distance(const QVector3D& point) const;
        bool front_facing(const QVector3D& direction) const;
        QVector3D normal() const;
    };

    class CBoundingBox {
    private:
        QVector3D m_vert_min;
        QVector3D m_vert_max;
    public:
        CBoundingBox() : m_vert_min(QVector3D(-1.0, -1.0, -1.0)), m_vert_max(QVector3D(1.0, 1.0, 1.0)) {}
        CBoundingBox(const QVector3D& vert_min, const QVector3D& vert_max) : m_vert_min(vert_min), m_vert_max(vert_max) {}
        ~CBoundingBox() {}
        void get_min(QVector3D& result) const;
        void get_max(QVector3D& result) const;
        qreal min_distance_squared(const QVector3D& point) const;
        qreal max_distance_squared(const QVector3D& point) const;
        void vertex_positive(const QVector3D& normal, QVector3D& result) const;
        void vertex_negative(const QVector3D& normal, QVector3D& result) const;
        QVector3D vert_min() const;
        QVector3D vert_max() const;
    };

    class CBoundingFrustum {
    private:
        CPlane m_planes[6];
    public:
        CBoundingFrustum() {}
        CBoundingFrustum(const QMatrix4x4& modelviewproj);
        void from_matrix(const QMatrix4x4& modelviewproj);
        CPlane plane_at(int index) const;
    };

    class CBoundingSphere {
    private:
        QVector3D m_center;
        qreal m_radius;
    public:
        CBoundingSphere() : m_center(QVector3D(0.0, 0.0, 0.0)), m_radius(0.0) {}
        CBoundingSphere(const QVector3D& center, qreal radius) : m_center(center), m_radius(radius) {}
        ~CBoundingSphere() {}
        QVector3D center() const;
        qreal radius() const;
    };

    class CCollision {
    public:
        enum ECollisionType {
            CONTAINS,
            INTERSECTS,
            NONE
        };
        static inline ECollisionType contains(const CBoundingBox& box_1, const CBoundingBox& box_2);
        static inline ECollisionType contains(const CBoundingBox& box, const CBoundingFrustum& frustum);
        static inline bool intersects(const CBoundingBox& box, const CBoundingSphere& sphere);
    };
}
#endif // UTILITY_H
