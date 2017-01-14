#ifndef CQUADTREENODE_H
#define CQUADTREENODE_H

#include "cselection.h"

namespace CDLOD {
    enum ESelectionResult {
        OUT_OF_FRUSTRUM,
        OUT_OF_RANGE,
        SELECTED
    };

    class CQuadtreeNode {
    public:
        CQuadtreeNode();
        ESelectionResult select()
    };
}

#endif // CQUADTREENODE_H
