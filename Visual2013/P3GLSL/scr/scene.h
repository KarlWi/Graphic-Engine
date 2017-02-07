#ifndef _scene_H
#define _scene_H
#include "BOX.h"

#include "camera.h"
#include "object.h"
#include "program.h"

#include "BOX.h"
#include "auxiliar.h"

#include <windows.h>

#include <gl/glew.h>
#include <gl/gl.h>
#define SOLVE_FGLUT_WARNING
#include <gl/freeglut.h> 
#include <iostream>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class scene{

public:


	camera cam;

	

	unsigned int ambientLight;
	glm::vec3 ambientLightValue;




	//Luces direccionales
	unsigned int directionalLightIntensity;
	glm::vec3 directionalLightIntensityValue[8];
	unsigned int directionalLightDir;
	glm::vec3 directionalLightDirValue[8];
	unsigned int nDirectionalLight;
	int nDirectionalLightValue;

	//Luces puntuales
	unsigned int pointLightIntensity;
	glm::vec3 pointLightIntensityValue[8];
	unsigned int pointLightPos;
	glm::vec3 pointLightPosValue[8];
	unsigned int nPointLight;
	int nPointLightValue;

	//Luces focales
	unsigned int focalLightIntensity;
	glm::vec3 focalLightIntensityValue[8];
	unsigned int focalLightDir;
	glm::vec3 focalLightDirValue[8];
	unsigned int focalLightPos;
	glm::vec3 focalLightPosValue[8];
	unsigned int focalLightAperture;
	float focalLightApertureValue[8];
	unsigned int nFocalLight;
	int nFocalLightValue;

	object  objs[8];
	int nObjects;

	float objsKa[8];
	float objsKd[8];
	float objsKs[8];
	float objsAlpha[8];


	bool rotate;
	program prog;

	scene();

	void setCamera(camera cm);

	void setDirLight(glm::vec3 intensity, glm::vec3 direction);

	void setPointLight(glm::vec3 intensity, glm::vec3  pos);

	void setAmbientLight(glm::vec3 intensity);

	void setFocalLight(glm::vec3 intensity, glm::vec3 dir, glm::vec3  pos, float aperture);

	void setObject(glm::mat4 model, program prog, float Kambiental, float Kdiffuse, float Kspecular, float alpha);

	void render();

	void destroyScene();

};

#endif