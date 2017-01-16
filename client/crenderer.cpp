#include "crenderer.h"

CRenderer::CRenderer() {

}

void CRenderer::render_scene(const QScopedPointer<CScene>& scene_ptr) {
    scene_ptr->render();
}
