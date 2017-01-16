#ifndef CSELECTION_H
#define CSELECTION_H

#include <qt5/QtCore/QSharedPointer>
#include <qt5/QtCore/QVector>
#include "utility.h"
#include "ccamera.h"
#include "csettings.h"

namespace CDLOD {
    /*!
     * \brief The CSelection class
     * Represents the current selection which will be rendered and contains all information needed to
     * render the terrain.
     */
    class CSelection {
    public:
        /*!
         * \brief The CSelectionNode class
         * We do not want to store any data in CQuadtreeNode class because it is too expensive.
         * Instead of this, we are going to store all necessary data only for nodes, selected
         * for rendering. Despite the seeming similarity with the CQuadtreeNode class, the
         * CSelectionNode class is completely different. It does not represent the quadtree node
         * exactly but stores all necessary data for rendering.
         */
        class CSelectionNode {
        private:
            unsigned int m_x;               ///< x-coordinate of the top left corner
            unsigned int m_y;               ///< y-coordinate of the top left corner
            unsigned int m_lod;             ///< Level of detail for this node
            size_t m_size;                  ///< Size of the node's bounding square on the height map
            bool m_top_left;                ///< True if top left child in the corresponding CQuadtreeNode exists
            bool m_top_right;               ///< True if top right child in the corresponding CQuadtreeNode exists
            bool m_bottom_left;             ///< True if bottom left child in the corresponding CQuadtreeNode exists
            bool m_bottom_right;            ///< True if bottom right child in the corresponding CQuadtreeNode exists
        public:
            CSelectionNode() {}
            CSelectionNode(unsigned int x, unsigned int y, unsigned int lod, size_t size, bool top_left, bool top_right,
                           bool bottom_left, bool bottom_right);
            Math::CBoundingBox bounding_box(int xsize, int ysize) const;
        };

    private:
        QSharedPointer<CCamera> m_camera;
        QSharedPointer<CSettings> m_settings;
        QVector<QSharedPointer<CSelectionNode>> m_selection;
        int m_size;
//        bool m_small_visible_distance;
    public:
        CSelection(QSharedPointer<CCamera>& camera, QSharedPointer<CSettings>& settings);
        /*!
         * \brief      Returns the visibility range for the given LOD level
         * \param[in]  level
         * \return                              visibility range for the given level
         */
        qreal visibiliry_range(short level) const;
        /*!
         * \brief      Returns observer's position
         * \return                              position
         */
        const QVector3D& observer_position() const;
        /*!
         * \brief      Returns maximum LOD level, which still will be processed
         * \return                              maximum LOD level
         */
        short max_lod_level() const;
        /*!
         * \brief      Returns current selection size
         * \return                              selection size
         */
        int selection_size() const;
        /*!
         * \brief      Returns maximum selection size
         * \return                              maximum selection size
         */
        int max_selection_size() const;
        /*!
         * \brief      Add the given node to the selection
         * \param[in]  node_ptr                 the given node
         */
        void push_node(QSharedPointer<CQuadtreeNode>& node_ptr);
        /*!
         * \brief      Returns pointer to the CSettings instance
         * \return                              pointer to the CSettings instance
         */
        QSharedPointer<CSettings> settings();
        /*!
         * \brief      Set the small_visible_distance flag
         * \param[in]  value                    the flag value
         */
//        void set_small_visible_distance(bool value);
        /*!
         * \brief      Returns distance at which morph begins
         * \param[in]  level                    current LOD level
         * \return     distance
         */
        qreal morph_start(short level);
    };
}

#endif // CSELECTION_H
