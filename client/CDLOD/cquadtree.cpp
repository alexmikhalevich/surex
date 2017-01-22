#include "cquadtree.h"

using namespace LOD;

CQuadtree::CQuadtree(int x_vert, int y_vert, const QSharedPointer<QOpenGLShaderProgram>& shader_program,
                     const QVector<QSharedPointer<QOpenGLTexture> >& textures, const QSharedPointer<CPlanetHeightmap>& heightmap) {
    m_xvert = x_vert;
    m_yvert = y_vert;
    m_shader_program = shader_program;
    m_textures = textures;
    m_heightmap = heightmap;
}

void CQuadtree::init() {
    qreal detail_balance = 1.0;
    qreal coeff = CSettings::lod_level_distance_ratio();
    for(int i = 0; i < CSettings::max_lod_level(); ++i) {
        m_lod_vis_distance_ratios[i] = detail_balance;
        detail_balance *= coeff;
    }
}

void CQuadtree::select(Math::ECubeFace face, float min_height, float max_height, float radius) {
    m_root.reset(new CQuadtreeNode(face, min_height, max_height, radius));
    int size = 0;   //TODO: calculate size as function from radius
    m_root->select(false, 0, 0, CSettings::max_lod_level(), size, m_xvert, m_yvert, m_shader_program,
                   m_textures, m_heightmap);
}
