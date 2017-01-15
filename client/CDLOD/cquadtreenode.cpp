#include "cquadtreenode.h"

using namespace CDLOD;

Math::CBoundingBox CQuadtreeNode::_bounding_box(int xsize, int ysize) {
    //TODO
}

ESelectionResult CQuadtreeNode::select(CSelection& selection, bool parent_in_frustum, int x, int y, int lod, size_t size) {
    Math::CBoundingBox bounding_box = get_bounding_box();
    Math::CCollision::ECollisionType frustum_collision = parent_in_frustum ? Math::CCollision::ECollisionType::CONTAINS
                                                                           : Math::CCollision::contains(bounding_box, selection.camera_frustum());
    if(frustum_collision == Math::CCollision::ECollisionType::NONE) {
        return ESelectionResult::OUT_OF_FRUSTUM;
    }
    qreal distance_limit = selection.visibiliry_range(m_level);
    if(!Math::CCollision::intersects(bounding_box, Math::CBoundingSphere(selection.observer_position(), distance_limit))) {
        return ESelectionResult::OUT_OF_RANGE;
    }

    ESelectionResult top_left_result = ESelectionResult::UNDEFINED;
    ESelectionResult top_right_result = ESelectionResult::UNDEFINED;
    ESelectionResult bottom_left_result = ESelectionResult::UNDEFINED;
    ESelectionResult bottom_right_result = ESelectionResult::UNDEFINED;
    if(m_level != selection.max_lod_level()) {
        qreal next_distance_limit =  selection.visibiliry_range(m_level + 1);
        if(Math::CCollision::intersects(bounding_box, Math::CBoundingSphere(selection.observer_position(), next_distance_limit))) {
            bool in_frustum = (frustum_collision == Math::CCollision::ECollisionType::CONTAINS);
            if(!m_top_left.isNull())
                top_left_result = m_top_left->select(selection, in_frustum, x, y, lod - 1, size / 2);
            if(!m_top_right.isNull())
                top_right_result = m_top_right->select(selection, in_frustum, x + size / 2, y, lod - 1, size / 2);
            if(!m_bottom_left.isNull())
                bottom_left_result = m_bottom_left->select(selection, in_frustum, x, y + size / 2, lod - 1, size / 2);
            if(!m_bottom_right.isNull())
                bottom_right_result = m_bottom_right->select(selection, in_frustum, x + size / 2, y + size / 2, lod - 1, size / 2);
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
            && selection.selection_size() < selection.max_selection_size()) {
        selection.push_node(QSharedPointer<CQuadtreeNode>(new CSelection::CSelectionNode(x, y, lod, size, !remove_top_left, !remove_top_right,
                                                                                         !remove_bottom_left, !remove_bottom_right)));
//        if(m_level != 0) {
//            qreal camera_distance = qSqrt(bounding_box.max_distance_squared(selection.observer_position()));
//            qreal morph_start = selection.morph_start(selection.max_lod_level() - m_level + 1);
//            if(camera_distance > morph_start)
//                selection.set_small_visible_distance(true);
//        }
        return ESelectionResult::SELECTED;
    }
    if(top_left_result == ESelectionResult::SELECTED || top_right_result == ESelectionResult::SELECTED
            || bottom_left_result == ESelectionResult::SELECTED || bottom_right_result == ESelectionResult::SELECTED) {
        return ESelectionResult::SELECTED;
    }
    return ESelectionResult::OUT_OF_FRUSTUM;
}
