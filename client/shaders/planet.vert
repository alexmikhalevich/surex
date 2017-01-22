attribute vec3 vertex;
attribute vec2 heightmap_coords;
attribute vec2 vertex_tex_coords;


uniform mat4 qt_ModelViewProjectionMatrix;
uniform sampler2D heightmap;
uniform float radius;
uniform float scale;
uniform float morph_val;
uniform float min_height;
uniform float max_height;
uniform vec2 grid_dim;
uniform int cube_face_num;

varying vec3 vertex_normal;
varying vec3 mapped_vertex;

float height(in vec4 color) {
    return min_height + ((max_height - min_height) / 255) * color.r;
}

vec3 morph_vertex(in vec2 grid_pos, in vec2 position, in vec2 translation, in float morph) {
    vec2 vert = position * scale + translation;
    vec2 frac_part = fract(grid_pos * grid_dim * 0.5) * 0.2 / grid_dim;
    return vert - frac_part * scale * morph;
}

//using Philip Nowell's formula from here: http://mathproofs.blogspot.ru/2005/07/mapping-cube-to-sphere.html
vec3 map_to_sphere(in vec3 point) {
    float x2 = point.x * point.x;
    float y2 = point.y * point.y;
    float z2 = point.z * point.z;
    vec3 result = vec3(point.x * sqrt(1.0 - (y2 * 0.5) - (z2 * 0.5) + ((y2 * z2) / 3.0)),
                       point.y * sqrt(1.0 - (z2 * 0.5) - (x2 * 0.5) + ((x2 * z2) / 3.0)),
                       point.z * sqrt(1.0 - (x2 * 0.5) - (y2 * 0.5) + ((y2 * x2) / 3.0)));
    return result;

}

vec3 normalized(in vec3 vector) {
    float length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    return vec3(vector.x / length, vector.y / length, vector.z / length);
}

void main(void) {
    vec4 heightmap_color = texture2D(heightmap, heightmap_coords);

    //morphing our vertex
    if(cube_face_num == 0)
        mapped_vertex = morph_vertex(vec2(abs(-1 - vertex.x) / 2, abs(-1 - vertex.y) / 2), vertex.xy,
                                     vec2(-1.0, -1.0), morph_val);
    else if(cube_face_num == 1)
        mapped_vertex = morph_vertex(vec2(abs(-1 - vertex.x) / 2, abs(-1 - vertex.z) / 2), vertex.xz,
                                     vec2(-1.0, -1.0), morph_val);
    else if(cube_face_num == 2)
        mapped_vertex = morph_vertex(vec2(abs(-1 - vertex.y) / 2, abs(-1 - vertex.z) / 2), vertex.yz,
                                     vec2(-1.0, -1.0), morph_val);
    else if(cube_face_num == 3)
        mapped_vertex = morph_vertex(vec2(abs(1 - vertex.x) / 2, abs(1 - vertex.y) / 2), vertex.xy,
                                     vec2(1.0, 1.0), morph_val);
    else if(cube_face_num == 4)
        mapped_vertex = morph_vertex(vec2(abs(1 - vertex.x) / 2, abs(1 - vertex.z) / 2), vertex.xz,
                                     vec2(1.0, 1.0), morph_val);
    else if(cube_face_num == 5)
        mapped_vertex = morph_vertex(vec2(abs(1 - vertex.y) / 2, abs(1 - vertex.z) / 2), vertex.yz,
                                     vec2(1.0, 1.0), morph_val);

    //making sphere
    mapped_vertex = map_to_sphere(mapped_vertex);
    vertex_normal = normalized(mapped_vertex);
    mapped_vertex = mapped_vertex * radius;

    //making landscape
    mapped_vertex = mapped_vertex + vertex_normal * height(heightmap_color);

    gl_Position = qt_ModelViewProjectionMatrix * mapped_vertex;
}
