#ifndef CSELECTION_H
#define CSELECTION_H

#include <qt5/QtCore/QSharedPointer>
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
    private:
        QSharedPointer<CCamera> m_camera;
        QSharedPointer<CSettings> m_settings;
        int m_size;
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
    };
}

#endif // CSELECTION_H
