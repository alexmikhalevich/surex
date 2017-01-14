#ifndef CQUADTREE_H
#define CQUADTREE_H

#include <qt5/QtCore/QScopedPointer>
#include "csettings.h"
#include "cselection.h"
#include "cquadtreenode.h"

namespace CDLOD {
    class CQuadtree {
    private:
        QScopedPointer<CQuadtreeNode> m_root;
    public:
        CQuadtree();
        void init(QScopedPointer<CSettings>& settings_ptr);
        void select(CSelection& selection);
    };
}

#endif // CQUADTREE_H
