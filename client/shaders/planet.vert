attribute vec3 vertex;
attribute vec2 heightmap_coords;

uniform mat4 qt_ModelViewProjectionMatrix;
uniform sampler2D heightmap;
uniform float radius;

varying vec3 vertex_normal;
varying vec3 mapped_vertex;

float height(in vec4 color) {
    //TODO
}

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

void main(void)
{
    vec4 heightmap_color = texture2D(heightmap, heightmap_coords);
    mapped_vertex = map_to_sphere(vertex);
    vertex_normal = normalized(mapped_vertex);
    mapped_vertex = mapped_vertex * radius;
    mapped_vertex = mapped_vertex + vertex_normal * height(heightmap_color);
    gl_Position = qt_ModelViewProjectionMatrix * mapped_vertex;
}
