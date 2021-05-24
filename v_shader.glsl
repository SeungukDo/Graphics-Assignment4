#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vUV;

out vec4 color;

out vec3 fN;
out vec3 fE;
out vec3 fL;
out vec3 pfL;
out vec2 UV;

uniform mat4 transform;
uniform mat4 model_view;
uniform mat4 projection;
uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;
uniform vec4 LightPosition;
uniform vec4 PLightPosition;
uniform float Shininess;
uniform bool Gouraud;

void main()
{
    if(Gouraud == true){
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


        vec3 pL = normalize(PLightPosition.xyz - pos);
        vec3 pE = normalize(-pos);
        vec3 pH = normalize(pL + pE);
        vec3 pN = normalize(model_view * transform * vec4(vNormal, 0.0)).xyz;

        vec4 pambient = AmbientProduct;
        float pKd = max(dot(pL, pN), 0.0);
        vec4 pdiffuse = pKd * DiffuseProduct;
        float pKs = pow(max(dot(pN, pH), 0.0), Shininess);
        vec4 pspecular = pKs * SpecularProduct;
        if(dot(pL, pN) < 0.0) pspecular = vec4(0.0, 0.0, 0.0, 1.0);

        gl_Position = projection * model_view * transform * vec4(Position.x, Position.y, Position.z, 1.0);

        color = (ambient + diffuse + specular + pambient + pdiffuse + pspecular) * 0.5;
        color.a = 1.0;

        UV = vUV;
    }
    else{
        fN = (model_view * transform * vec4(vNormal, 0.0)).xyz;
        fE = -(model_view * transform * vec4(Position.x, Position.y, Position.z, 1.0)).xyz;
        fL = LightPosition.xyz;

        pfL = PLightPosition.xyz;

        if(LightPosition.w != 0.0){
            fL = LightPosition.xyz + fE;
        }

        if(PLightPosition.w != 0.0){
            pfL = PLightPosition.xyz + fE;
        }

        gl_Position = projection * model_view * transform * vec4(Position.x, Position.y, Position.z, 1.0);

        UV = vUV;
    }
}