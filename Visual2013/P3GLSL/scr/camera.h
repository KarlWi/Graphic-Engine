#ifndef _camera_H
#define _camera_H
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

class camera{
public:
	glm::mat4	proj;
	glm::mat4	view;

	camera();
	camera(glm::mat4 proj, glm::mat4 view);
	void configCamera(float z);



};











#endif