#include "cquadtreenode.h"

using namespace CDLOD;

CQuadtreeNode::CQuadtreeNode() {}

ESelectionResult CQuadtreeNode::select(CSelection& selection, bool parent_in_frustum) {
    Math::CBoundingBox bounding_box = get_bounding_box();
    Math::CCollision::ECollisionType frustum_collision = parent_in_frustum ? Math::CCollision::ECollisionType::CONTAINS
                                                                           : Math::CCollision::contains(bounding_box, selection.camera_frustum());
    if(frustum_collision == Math::CCollision::ECollisionType::NONE) {
        return ESelectionResult::OUT_OF_FRUSTUM;
    }
}
