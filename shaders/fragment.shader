#version 400

out vec4 frag_color;
in vec2 data;

uniform sampler2D tex;

void main() {
  frag_color = texture(tex, data) * vec4(clamp(data.y / 1.5 + 0.7, 0.0, 1.0));
  // frag_color = vec4(texture(tex, data).xyz, 1.0);
}
