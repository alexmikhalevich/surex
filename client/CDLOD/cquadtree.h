#ifndef CQUADTREE_H
#define CQUADTREE_H

#include <qt5/QtCore/QScopedPointer>
#include "csettings.h"
#include "cselection.h"
#include "cquadtreenode.h"
#include "utility.h"

namespace CDLOD {
    /*!
     * \brief The CQuadtree class
     * Quadtree implementation.
     */
    class CQuadtree {
    private:
        QScopedPointer<CQuadtreeNode> m_root;       ///< Pointer to the root node in the tree
        QVector<qreal> m_lod_vis_distance_ratios;   ///< LOD visibility range distribution
        /*!
         * \brief Cleans all CQuadtree stuff
         */
        void _clean();
    public:
        CQuadtree() {}
        /*!
         * \brief           Initialises the tree
         * \param[in]       settings_ptr        different system settings
         */
        void init(QScopedPointer<CSettings>& settings_ptr);
        /*!
         * \brief           Launches a recursive tree traversal
         * \param[out]      selection           CSelection instance which contains all information needed to render the terrain
         */
        void select(CSelection& selection);
    };
}

#endif // CQUADTREE_H
