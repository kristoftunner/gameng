
#type vertex
#version 330 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec2 a_textCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

out vec3 v_position;
out vec2 v_textCoord;
void main()
{
  v_textCoord = a_textCoord;
  v_position = a_position;
  gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

layout(location=0) out vec4 color;

in vec2 v_textCoord;

uniform sampler2D u_texture;

void main()
{
  color = texture(u_texture, v_textCoord);
}

