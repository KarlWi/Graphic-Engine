#include "attributes.h"

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

attributes::attributes(int prog){
	attributes::program;
	program = prog;
}

int attributes::getAttribute(const char *att){
	attributes::attribute;
	attribute = glGetAttribLocation(attributes::program, att);
	std::cout << attribute << std::endl;
	return attribute;
}

void attributes::bindAttribute(int prog, int value, const char *att){
	glBindAttribLocation(attributes::program, value, att);
}