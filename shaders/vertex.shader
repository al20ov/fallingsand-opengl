#version 400

in vec3 vp;

out float data;

void main() {
  gl_Position = vec4(vp.xy, 0.0, 1.0);
  data = vp.z;
}
