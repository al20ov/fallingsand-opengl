#version 400

in vec4 vp;

out vec2 data;

void main() {
  gl_Position = vec4(vp.xy, 0.0, 1.0);
  data = vec2(vp.zw);
}
