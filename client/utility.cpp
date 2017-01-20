#include "utility.h"

using namespace Math;

void CBoundingBox::get_max(QVector3D& result) const {
    result = m_vert_max;
}

void CBoundingBox::get_min(QVector3D& result) const {
    result = m_vert_min;
}

qreal CBoundingBox::max_distance_squared(const QVector3D& point) const {
    qreal distance = 0.0;
    qreal coeff = 0.0;

    coeff = qMax(qAbs(point.x() - m_vert_max.x()), qAbs(point.x() - m_vert_min.x()));
    distance += coeff * coeff;
    coeff = qMax(qAbs(point.y() - m_vert_max.y()), qAbs(point.y() - m_vert_min.y()));
    distance += coeff * coeff;
    coeff = qMax(qAbs(point.z() - m_vert_max.z()), qAbs(point.z() - m_vert_min.z()));
    distance += coeff * coeff;

    return distance;
}

qreal CBoundingBox::min_distance_squared(const QVector3D& point) const {
    qreal distance = 0.0;

    if(point.x() < m_vert_min.x()) {
        qreal d = point.x() = m_vert_min.x();
        distance += d * d;
    }
    else if(point.x() > m_vert_max.x()) {
        qreal d = point.x() = m_vert_max.x();
        distance += d * d;
    }

    if(point.y() < m_vert_min.y()) {
        qreal d = point.y() = m_vert_min.y();
        distance += d * d;
    }
    else if(point.y() > m_vert_max.y()) {
        qreal d = point.y() = m_vert_max.y();
        distance += d * d;
    }

    if(point.z() < m_vert_min.z()) {
        qreal d = point.z() = m_vert_min.z();
        distance += d * d;
    }
    else if(point.z() > m_vert_max.z()) {
        qreal d = point.z() = m_vert_max.z();
        distance += d * d;
    }

    return distance;
}

void CBoundingBox::vertex_positive(const QVector3D& normal, QVector3D& result) const {
    result = m_vert_min;
    if(normal.x() >= 0)
        result.setX(m_vert_max.x());
    if(normal.y() >= 0)
        result.setY((m_vert_max.y());
    if(normal.z() >= 0)
        result.setZ(m_vert_max.z());
}

void CBoundingBox::vertex_negative(const QVector3D& normal, QVector3D& result) const {
    result = m_vert_max;
    if(normal.x() >= 0)
        result.setX(m_vert_min.x());
    if(normal.y() >= 0)
        result.setY(m_vert_min.y());
    if(normal.z() >= 0)
        result.setZ(m_vert_min.z());
}

void CPlane::set_normal(const QVector3D& normal) {
    m_normal = normal;
}

void CPlane::set_distance(qreal distance) {
    m_distance = distance;
}

bool CPlane::front_facing(const QVector3D& direction) const {
    return (QVector3D::dotProduct(direction, _normal) <= 0);
}

qreal CPlane::distance(const QVector3D& point) const {
    return QVector3D::dotProduct(point, m_normal) + m_distance;
}

QVector3D CPlane::normal() const {
    return m_normal;
}

QVector3D CBoundingSphere::center() const {
    return m_center;
}

qreal CBoundingSphere::radius() const {
    return m_radius;
}

CBoundingFrustum::CBoundingFrustum(const QMatrix4x4& modelviewproj) {
    from_matrix(modelviewproj);
}

void CBoundingFrustum::from_matrix(const QMatrix4x4& modelviewproj) {
    //left plane
    m_planes[0].set_normal(QVector3D(modelviewproj.row(0).w() + modelviewproj.row(0).x(),
                           modelviewproj.row(1).w() + modelviewproj.row(1).x(),
                           modelviewproj.row(2).w() + modelviewproj.row(2).x()));
    m_planes[0].set_distance(QVector3D(modelviewproj.row(3).w() + modelviewproj.row(3).x()));

    //right plane
    m_planes[1].set_normal(QVector3D(modelviewproj.row(0).w() - modelviewproj.row(0).x(),
                           modelviewproj.row(1).w() - modelviewproj.row(1).x(),
                           modelviewproj.row(2).w() - modelviewproj.row(2).x()));
    m_planes[1].set_distance(QVector3D(modelviewproj.row(3).w() - modelviewproj.row(3).x()));

    //top plane
    m_planes[2].set_normal(QVector3D(modelviewproj.row(0).w() - modelviewproj.row(0).y(),
                           modelviewproj.row(1).w() - modelviewproj.row(1).y(),
                           modelviewproj.row(2).w() - modelviewproj.row(2).y()));
    m_planes[2].set_distance(QVector3D(modelviewproj.row(3).w() - modelviewproj.row(3).y()));

    //bottom plane
    m_planes[3].set_normal(QVector3D(modelviewproj.row(0).w() + modelviewproj.row(0).y(),
                           modelviewproj.row(1).w() + modelviewproj.row(1).y(),
                           modelviewproj.row(2).w() + modelviewproj.row(2).y()));
    m_planes[3].set_distance(QVector3D(modelviewproj.row(3).w() + modelviewproj.row(3).y()));

    //near plane
    m_planes[4].set_normal(QVector3D(modelviewproj.row(0).z(),
                           modelviewproj.row(1).z(),
                           modelviewproj.row(2).z()));
    m_planes[4].set_distance(QVector3D(modelviewproj.row(3).z()));

    //far plane
    m_planes[5].set_normal(QVector3D(modelviewproj.row(0).w() + modelviewproj.row(0).z(),
                           modelviewproj.row(1).w() + modelviewproj.row(1).z(),
                           modelviewproj.row(2).w() + modelviewproj.row(2).z()));
    m_planes[5].set_distance(QVector3D(modelviewproj.row(3).w() + modelviewproj.row(3).z()));
}

CPlane CBoundingFrustum::plane_at(int index) const {
    if(index >= 0 && index < 6)
        return m_planes[index];
}

CCollision::ECollisionType CCollision::contains(const CBoundingBox& box_1, const CBoundingBox& box_2) {
    qreal bottom_1 = box_1.vert_min().y();
    qreal top_1 = box_1.vert_max().y();
    qreal left_1 = box_1.vert_min().x();
    qreal right_1 = box_1.vert_max().x();
    qreal near_1 = box_1.vert_min().z();
    qreal far_1 = box_1.vert_max().z();

    qreal bottom_2 = box_2.vert_min().y();
    qreal top_2 = box_2.vert_max().y();
    qreal left_2 = box_2.vert_min().x();
    qreal right_2 = box_2.vert_max().x();
    qreal near_2 = box_2.vert_min().z();
    qreal far_2 = box_2.vert_max().z();

    if(top_1 > bottom_2 && bottom_1 < top_2 && left_1 < right_2 && right_1 > left_2 && far_1 > near_2 && near_1 < far_2) {
        if(top_1 >= top_2 && bottom_1 <= top_2 && left_1 <= left_2 && right_1 >= right_2 && near_1 <= near_2 && far_1 >= far_2) {
            return ECollisionType::CONTAINS;
        }
        return ECollisionType::INTERSECTS;
    }
    return ECollisionType::NONE;
}

CCollision::ECollisionType CCollision::contains(const CBoundingBox& box, const CBoundingFrustum& frustum) {
    ECollisionType result = ECollisionType::CONTAINS;
    for(int i = 0; i < 6; ++i) {
        QVector3D vertex;
        box.vertex_positive(frustum.plane_at(i).normal(), vertex);
        if(frustum.plane_at(i).distance(vertex) < 0)
            return ECollisionType::NONE;
        box.vertex_negative(frustum.plane_at(i).normal(), vertex);
        if(frustum.plane_at(i).distance(vertex) < 0)
            result = ECollisionType::INTERSECTS;
    }
    return result;
}

bool CCollision::intersects(const CBoundingBox& box, const CBoundingSphere& sphere) {
    return box.min_distance_squared(sphere.center()) <= sphere.radius() * sphere.radius();
}
