#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 vNormal;

out vec4 color;

uniform mat4 transform;
uniform mat4 model_view;
uniform mat4 projection;
uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;
uniform vec4 LightPosition;
uniform float Shininess;
uniform bool Gouraud;

void main()
{
    vec3 pos = (model_view * transform * vec4(Position.x, Position.y, Position.z, 1.0)).xyz;

    vec3 L = normalize(LightPosition.xyz - pos);
    vec3 E = normalize(-pos);
    vec3 H = normalize(L + E);

    vec3 N = normalize(model_view * transform * vec4(vNormal, 0.0)).xyz;

    vec4 ambient = AmbientProduct;
    float Kd = max(dot(L, N), 0.0);
    vec4 diffuse = Kd * DiffuseProduct;
    float Ks = pow(max(dot(N, H), 0.0), Shininess);
    vec4 specular = Ks * SpecularProduct;
    if(dot(L, N) < 0.0) specular = vec4(0.0, 0.0, 0.0, 1.0);

    gl_Position = projection * model_view * transform * vec4(Position.x, Position.y, Position.z, 1.0);
    color = ambient + diffuse + specular;
    color.a = 1.0;
}