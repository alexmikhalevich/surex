#ifndef CSELECTION_H
#define CSELECTION_H

#include <qt5/QtCore/QSharedPointer>
#include <qt5/QtCore/QVector>
#include "utility.h"
#include "ccamera.h"
#include "csettings.h"

namespace CDLOD {
    class CQuadtreeNode;
    /*!
     * \brief The CSelection class
     * Represents the current selection which will be rendered and contains all information needed to
     * render the terrain.
     */
    class CSelection {
    private:
        QSharedPointer<CCamera> m_camera;
        QSharedPointer<CSettings> m_settings;
        QVector<QSharedPointer<CQuadtreeNode>> m_selection;
        int m_size;
        bool m_small_visible_distance;
    public:
        CSelection();
        /*!
         * \brief      Returns the visibility range for the given LOD level
         * \param[in]  level
         * \return     visibility range for the given level
         */
        qreal visibiliry_range(short level) const;
        /*!
         * \brief      Returns observer's position
         * \return     position
         */
        const QVector3D& observer_position() const;
        /*!
         * \brief      Returns maximum LOD level, which still will be processed
         * \return     maximum LOD level
         */
        short max_lod_level() const;
        /*!
         * \brief      Returns current selection size
         * \return     selection size
         */
        int selection_size() const;
        /*!
         * \brief      Returns maximum selection size
         * \return     maximum selection size
         */
        int max_selection_size() const;
        /*!
         * \brief      Add the given node to the selection
         * \param[in]  node_ptr the given node
         */
        void push_node(QSharedPointer<CQuadtreeNode>& node_ptr);
        /*!
         * \brief      Returns pointer to the CSettings instance
         * \return     pointer to the CSettings instance
         */
        QSharedPointer<CSettings> settings();
        /*!
         * \brief      Set the small_visible_distance flag
         * \param[in]  value the flag value
         */
        void set_small_visible_distance(bool value);
        /*!
         * \brief      Returns distance at which morph begins
         * \param[in]  level current LOD level
         * \return     distance
         */
        qreal morph_start(short level);
    };
}

#endif // CSELECTION_H
