#ifndef _uniforms_H
#define _uniforms_H
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

class uniforms{
public:
	int uniform;
	int program;

	uniforms(int prog);//Constructor, le pasamos 
	int getUniform(const char *uni);
	//void setUniform(auto uniformVar);
	//void setUniform(int prog, int value, const char *attribute);



};

#endif;