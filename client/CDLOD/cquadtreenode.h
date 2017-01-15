#ifndef CQUADTREENODE_H
#define CQUADTREENODE_H

#include <qt5/QtCore/qmath.h>
#include "cselection.h"

namespace CDLOD {
    /*!
     * \brief The ESelectionResult enum
     * Represents the status of the select operation
     */
    enum ESelectionResult {
        OUT_OF_FRUSTUM,
        OUT_OF_RANGE,
        SELECTED,
        UNDEFINED
    };

    /*!
     * \brief The CQuadtreeNode class
     * The Quadtree node representation
     */
    class CQuadtreeNode {
    private:
        QScopedPointer<CQuadtreeNode> m_top_left;
        QScopedPointer<CQuadtreeNode> m_bottom_left;
        QScopedPointer<CQuadtreeNode> m_top_right;
        QScopedPointer<CQuadtreeNode> m_bottom_right;

        Math::CBoundingBox _bounding_box(int xsize, int ysize);
    public:
        CQuadtreeNode() {}
        /*!
         * Recursively traverses the quadtree to create a subset of nodes representing the currently observable part of the terrain
         * \param[out]  selection          CSelection instance which contains all information needed to render the terrain
         * \param[in]   parent_in_frustum  flag which shows if the parent node is in frustum
         * \param[in]   x                  x-coordinate of the top-left corner of the parent node
         * \param[in]   y                  y-coordinate of the top-left corner of the parent node
         * \param[in]   lod                level of detail for the parent node
         * \param[in]   size               size of the parent node's bounding square
         * \return                         operation status
         */
        ESelectionResult select(CSelection& selection, bool parent_in_frustum, int x, int y, int lod, size_t size);
    };
}

#endif // CQUADTREENODE_H
