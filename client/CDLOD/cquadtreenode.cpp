#include "cquadtreenode.h"

using namespace LOD;

CQuadtreeNode::CQuadtreeNode(Math::ECubeFace face, float min_height, float max_height, float radius, const QSharedPointer<CCamera>& camera) {
    m_face = face;
    m_min_height = min_height / radius;
    m_max_height = max_height / radius;
    m_camera = camera;
    m_selection_size = 0;
}

Math::CBoundingBox CQuadtreeNode::_get_bounding_box(int x, int y, int size) const {
    Math::CBoundingBox result;
    if(m_face == Math::ECubeFace::XY_NEGATIVE)
        result = Math::CBoundingBox(QVector3D(x, y, -1 + m_min_height), QVector3D(x + size, y + size, -1 - m_max_height));
    else if(m_face == Math::ECubeFace::XY_POSITIVE)
        result = Math::CBoundingBox(QVector3D(x, y, 1 - m_min_height), QVector3D(x + size, y + size, 1 + m_max_height));
    else if(m_face == Math::ECubeFace::XZ_NEGATIVE)
        result = Math::CBoundingBox(QVector3D(x, -1 + m_min_height, y), QVector3D(x + size, -1 - m_max_height, y + size));
    else if(m_face == Math::ECubeFace::XZ_POSITIVE)
        result = Math::CBoundingBox(QVector3D(x, 1 - m_min_height, y), QVector3D(x + size, 1 + m_max_height, y + size));
    else if(m_face == Math::ECubeFace::YZ_NEGATIVE)
        result = Math::CBoundingBox(QVector3D(-1 + m_min_height, y, x), QVector3D(-1 + m_max_height, y + size, x + size));
    else if(m_face == Math::ECubeFace::YZ_POSITIVE)
        result = Math::CBoundingBox(QVector3D(1 - m_min_height, y, x), QVector3D(1 - m_max_height, y + size, x + size));
    return result;
}

bool CQuadtreeNode::_generate_mesh_chunk(int x_vert, int y_vert, QSharedPointer<QOpenGLShaderProgram>& shader_program,
                                         const QVector<QSharedPointer<QOpenGLTexture> >& textures,
                                         const QSharedPointer<CPlanetHeightmap>& heightmap) {
    m_mesh_chunk = QSharedPointer<CTerrainMeshChunk>(new CTerrainMeshChunk(shader_program, textures, heightmap));
    return m_mesh_chunk->create(x_vert, y_vert, m_face);
}

ESelectionResult CQuadtreeNode::select(bool parent_in_frustum, int x, int y, short lod, int size,
                                       int x_vert, int y_vert, QSharedPointer<QOpenGLShaderProgram>& shader_program,
                                       const QVector<QSharedPointer<QOpenGLTexture> >& textures,
                                       const QSharedPointer<CPlanetHeightmap>& heightmap) {
    Math::CBoundingBox bounding_box = _get_bounding_box(x, y, size);
    Math::CCollision::ECollisionType frustum_collision = parent_in_frustum ? Math::CCollision::ECollisionType::CONTAINS
                                                                           : Math::CCollision::contains(bounding_box, m_camera->frustum());
    if(frustum_collision == Math::CCollision::ECollisionType::NONE) {
        return ESelectionResult::OUT_OF_FRUSTUM;
    }
    qreal distance_limit = CSettings::visibility_range(lod);
    if(!Math::CCollision::intersects(bounding_box, Math::CBoundingSphere(m_camera->position(), distance_limit))) {
        return ESelectionResult::OUT_OF_RANGE;
    }

    ESelectionResult top_left_result = ESelectionResult::UNDEFINED;
    ESelectionResult top_right_result = ESelectionResult::UNDEFINED;
    ESelectionResult bottom_left_result = ESelectionResult::UNDEFINED;
    ESelectionResult bottom_right_result = ESelectionResult::UNDEFINED;
    if(lod != CSettings::max_lod_level()) {
        qreal next_distance_limit =  CSettings::visibility_range(lod + 1);
        if(Math::CCollision::intersects(bounding_box, Math::CBoundingSphere(m_camera->position(), next_distance_limit))) {
            bool in_frustum = (frustum_collision == Math::CCollision::ECollisionType::CONTAINS);
            if(!m_top_left.isNull())
                top_left_result = m_top_left->select(in_frustum, x, y, lod - 1, size / 2, x_vert, y_vert, shader_program,
                                                     textures, heightmap);
            if(!m_top_right.isNull())
                top_right_result = m_top_right->select(in_frustum, x + size / 2, y, lod - 1, size / 2, x_vert, y_vert,
                                                       shader_program, textures, heightmap);
            if(!m_bottom_left.isNull())
                bottom_left_result = m_bottom_left->select(in_frustum, x, y + size / 2, lod - 1, size / 2, x_vert, y_vert,
                                                           shader_program, textures, heightmap);
            if(!m_bottom_right.isNull())
                bottom_right_result = m_bottom_right->select(in_frustum, x + size / 2, y + size / 2, lod - 1, size / 2,
                                                             x_vert, y_vert, shader_program, textures, heightmap);
        }
    }

    bool remove_top_left = (top_left_result == ESelectionResult::OUT_OF_FRUSTUM)
            || (top_left_result == ESelectionResult::SELECTED);
    bool remove_top_right = (top_right_result == ESelectionResult::OUT_OF_FRUSTUM)
            || (top_right_result == ESelectionResult::SELECTED);
    bool remove_bottom_left = (bottom_left_result == ESelectionResult::OUT_OF_FRUSTUM)
            || (bottom_left_result == ESelectionResult::SELECTED);
    bool remove_bottom_right = (bottom_right_result == ESelectionResult::OUT_OF_FRUSTUM)
            || (bottom_right_result == ESelectionResult::SELECTED);
    if(!(remove_top_left && remove_top_right && remove_bottom_left && remove_bottom_right)
            && m_selection_size < CSettings::max_selection_size()) {
        if(m_mesh_chunk.isNull()) {
            if(!_generate_mesh_chunk(x_vert, y_vert, shader_program, textures, heightmap)) {
                //TODO: process this error
            }
        }
        m_mesh_chunk->set_scale(size);
        m_mesh_chunk->render();
        ++m_selection_size;
        return ESelectionResult::SELECTED;
    }
    if(top_left_result == ESelectionResult::SELECTED || top_right_result == ESelectionResult::SELECTED
            || bottom_left_result == ESelectionResult::SELECTED || bottom_right_result == ESelectionResult::SELECTED) {
        return ESelectionResult::SELECTED;
    }
    return ESelectionResult::OUT_OF_FRUSTUM;
}
