#version 330

in vec2 TexCoord;
in vec4 color;
in vec3 fN;
in vec3 fE;
in vec3 fL;
in vec3 pfL;
in vec2 UV;

uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;
uniform float Shininess;
uniform bool Gouraud;
out vec4 FragColor;
uniform vec4 ourColor;
uniform sampler2D myTexture;
uniform bool useTexture;

void main()
{
	if(!Gouraud){
		vec3 N = normalize(fN);
		vec3 E = normalize(fE);
		vec3 L = normalize(fL);

		vec3 H = normalize(L + E);

		vec4 ambient = AmbientProduct;
        float Kd = max(dot(L, N), 0.0);
        vec4 diffuse = Kd * DiffuseProduct;
        float Ks = pow(max(dot(N, H), 0.0), Shininess);
        vec4 specular = Ks * SpecularProduct;
        if(dot(L, N) < 0.0) specular = vec4(0.0, 0.0, 0.0, 1.0);


		vec3 pN = normalize(fN);
		vec3 pE = normalize(fE);
		vec3 pL = normalize(pfL);

		vec3 pH = normalize(pL + pE);

		vec4 pambient = AmbientProduct;
		float pKd = max(dot(pL, pN), 0.0);
		vec4 pdiffuse = pKd * DiffuseProduct;
		float pKs = pow(max(dot(pN, pH), 0.0), Shininess);
		vec4 pspecular = pKs * SpecularProduct;
		if(dot(pL, pN) < 0.0) pspecular = vec4(0.0, 0.0, 0.0, 1.0);

		vec4 Pcolor = (ambient + diffuse + specular + pambient + pdiffuse + pspecular) * 0.5;
		Pcolor.a = 1.0;

		if(useTexture == false){
		    FragColor = ourColor * Pcolor;
		   }
		else{
		    FragColor = vec4(texture(myTexture, UV)) * Pcolor;
		}
		//FragColor = ourColor * Pcolor;
	}
	else{
	    if(useTexture == false){
		    FragColor = color * ourColor;
		}
		else{
		    FragColor = texture(myTexture, UV);
		}
        //FragColor = color * ourColor;
	}
}