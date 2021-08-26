#version 400

out vec4 frag_color;
in float data;

void main() {
  frag_color = vec4(data, data, data, 1.0);
}
