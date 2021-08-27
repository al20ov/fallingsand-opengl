#version 400

out vec4 frag_color;
in vec2 data;

uniform sampler2D tex;

void main() {
  frag_color = texture(tex, data) * vec4(clamp(data.y / 2.0 + 0.5, 0.0, 1.0));
}
