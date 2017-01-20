#include "cscene.h"

CScene::CScene() {

}

void CScene::add_object(const QSharedPointer<IRenderable>& object) {
    m_objects.push_back(object);
}

void CScene::render() {
    for(int i = 0; i < m_objects.size(); ++i)
        m_objects.at(i)->render();
}
