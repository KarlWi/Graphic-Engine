#include "uniforms.h"

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

uniforms::uniforms(int prog){
	uniforms::program;
	program = prog;
}

int uniforms::getUniform(const char *uni){
	uniforms::uniform;
	uniform = glGetUniformLocation(uniforms::program, uni);
	return uniform;
}