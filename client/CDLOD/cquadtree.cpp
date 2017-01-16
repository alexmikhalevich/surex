#include "cquadtree.h"

using namespace CDLOD;

void CQuadtree::_clean() {

}

void CQuadtree::init(QSharedPointer<CSettings>& settings_ptr) {
    _clean();

    qreal detail_balance = 1.0;
    qreal coeff = settings_ptr->lod_level_distance_ratio();
    for(int i = 0; i < settings_ptr->max_lod_level(); ++i) {
        m_lod_vis_distance_ratios[i] = detail_balance;
        detail_balance *= coeff;
    }
}

void CQuadtree::select() {

}
