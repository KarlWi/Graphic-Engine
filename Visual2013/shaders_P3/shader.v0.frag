#version 330 core

out vec4 outColor;

in vec3 color;
in vec3 pos;
in vec3 norm;
in vec2 texCoord;

uniform sampler2D colorTex;
uniform sampler2D emiTex;

//Propiedades del objeto
uniform float Ka;
uniform float Kd;
uniform float Ks;
vec3 N;
//uniform float alpha = 1700.0;
uniform float alpha;
vec3 Ke;

//Propiedades de la luz
//vec3 Ia = vec3 (0.3);
uniform vec3 Ia;
//vec3 Id = vec3 (1.0);
//uniform vec3 I;
vec3 Is = vec3 (1.0);
//uniform vec3 Is;
//vec3 lpos = vec3 (0.0); 
uniform vec3 lpos;



//Luces direccionales
uniform vec3 directionalLightIntensity[8];
uniform vec3 directionalLightDir[8];
uniform int nDirectionalLight;

//Luces puntuales
uniform vec3 pointLightIntensity[8];
uniform vec3 pointLightPos[8];
uniform int nPointLight;

//Luces focales
uniform vec3 focalLightIntensity[8];
uniform vec3 focalLightDir[8];
uniform vec3 focalLightPos[8];
uniform float focalLightAperture[8];
uniform int nFocalLight;


vec3 Ka1;
vec3 Kd1;
vec3 Ks1;


vec3 shade();

void main()
{
	Ka1 = Ka*color;
	Kd1 = Kd*color;
	Ke = vec3(0.0);
	Ks1 = Ks*vec3 (1.0);

	N = normalize (norm);
	
	outColor = vec4(shade(), 1.0);   
}

vec3 shade()
{
	vec3 c = vec3(0.0);
	c = Ia * Ka1;



	//vec3 L = normalize (lpos - pos);
	//vec3 diffuse = I * Kd1 * dot (L,N);
	//c += clamp(diffuse, 0.0, 1.0);


	//LUCES PUNTUALES
	for(int i = 0; i<nPointLight;i++){
		vec3 L = normalize(pointLightPos[i]-pos);
		vec3 diffuse = Kd1*dot(N,L)*pointLightIntensity[i];
		c+=clamp(diffuse,0.0,1.0);
		vec3 V = normalize (-pos);
		vec3 R = normalize (reflect (-L,N));
		float factor = max (dot (R,V), 0.01);
		vec3 specular = Is*Ks1*pow(factor,alpha);
		c += clamp(specular, 0.0, 1.0);
	}

	//LUCES DIRECCIONALES

	for(int i = 0; i<nDirectionalLight;i++){
		vec3 L = normalize(directionalLightDir[i]);
		vec3 diffuse = Kd1*dot(N,L)*directionalLightIntensity[i];
		c+=clamp(diffuse,0.0,1.0);
	}


	//LUCES FOCALES

	for(int i = 0; i<nFocalLight;i++){
		vec3 L = normalize(focalLightPos[i]-pos);
		vec3 diffuse = vec3(0.0);
		if(dot(focalLightDir[i],-L) > cos(focalLightAperture[i])){
			diffuse = Kd1*dot(N,L)*focalLightIntensity[i]*((focalLightDir[i]*(-L) -cos(focalLightAperture[i]))/(1-cos(focalLightAperture[i])));
		}
		//else{
		//	diffuse = vec3(0.0);
		//}
		c+=clamp(diffuse,0.0,1.0);
	}


	
	//vec3 V = normalize (-pos);
	//vec3 R = normalize (reflect (-L,N));
	//float factor = max (dot (R,V), 0.01);
	//vec3 specular = Is*Ks1*pow(factor,alpha);
	//c += clamp(specular, 0.0, 1.0);

	c+=Ke;
	
	return c;
}


