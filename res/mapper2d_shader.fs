#version 330

out vec4 color;
uniform vec3 g_model_id;

void main()
{
    color = vec4(g_model_id,  1.0);
}