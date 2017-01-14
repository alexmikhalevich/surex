#include "utility.h"

using namespace Math;

void CBoundingBox::get_max(QVector3D& result) const {
    result = m_center + m_half_size;
}

void CBoundingBox::get_min(QVector3D& result) const {
    result = m_center - m_half_size;
}

qreal CBoundingBox::max_distance_squared(const QVector3D& point) const {
    qreal distance = 0.0;
    qreal coeff = 0.0;
    QVector3D min_vector, max_vector;
    get_max(max_vector);
    get_min(min_vector);

    coeff = qMax(qAbs(point.x() - max_vector.x()), qAbs(point.x() - min_vector.x()));
    distance += coeff * coeff;
    coeff = qMax(qAbs(point.y() - max_vector.y()), qAbs(point.y() - min_vector.y()));
    distance += coeff * coeff;
    coeff = qMax(qAbs(point.z() - max_vector.z()), qAbs(point.z() - min_vector.z()));
    distance += coeff * coeff;

    return distance;
}

qreal CBoundingBox::min_distance_squared(const QVector3D& point) const {
    QVector3D min_vector, max_vector;
    get_max(max_vector);
    get_min(min_vector);
    qreal distance = 0.0;

    if(point.x() < min_vector.x()) {
        qreal d = point.x() = min_vector.x();
        distance += d * d;
    }
    else if(point.x() > max_vector.x()) {
        qreal d = point.x() = max_vector.x();
        distance += d * d;
    }

    if(point.y() < min_vector.y()) {
        qreal d = point.y() = min_vector.y();
        distance += d * d;
    }
    else if(point.y() > max_vector.y()) {
        qreal d = point.y() = max_vector.y();
        distance += d * d;
    }

    if(point.z() < min_vector.z()) {
        qreal d = point.z() = min_vector.z();
        distance += d * d;
    }
    else if(point.z() > max_vector.z()) {
        qreal d = point.z() = max_vector.z();
        distance += d * d;
    }

    return distance;
}

void CBoundingBox::vertex_positive(const QVector3D& normal, QVector3D& result) const {
    QVector3D max_vector;
    get_min(result);
    get_max(max_vector);
    if(normal.x() >= 0)
        result.setX(max_vector.x());
    if(normal.y() >= 0)
        result.setY((max_vector.y());
    if(normal.z() >= 0)
        result.setZ(max_vector.z());
}

void CBoundingBox::vertex_negative(const QVector3D& normal, QVector3D& result) const {
    QVector3D min_vector;
    get_max(result);
    get_min(max_vector);
    if(normal.x() >= 0)
        result.setX(min_vector.x());
    if(normal.y() >= 0)
        result.setY(min_vector.y());
    if(normal.z() >= 0)
        result.setZ(min_vector.z());
}

QVector3D CBoundingBox::center() const {
    return m_center;
}

QVector3D CBoundingBox::half_size() const {
    return m_half_size;
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
