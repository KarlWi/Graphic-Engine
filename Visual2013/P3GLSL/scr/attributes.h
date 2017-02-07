#ifndef _attributes_H
#define _attributes_H
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

class attributes{
public:
	int attribute;
	int program;

	attributes(int prog);
	int getAttribute(const char *attribute);
	void bindAttribute(int prog, int value, const char *attribute);



};











#endif