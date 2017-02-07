#ifndef _program_H
#define _program_H
#include "BOX.h"

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

class program{
public:
	int vshader;
	int fshader;
	unsigned int prog;
	program(const char *vertexAddress, const char *fragAddress);
	GLuint loadShader(const char *fileName, GLenum type);
	program();
	
	


};

#endif;