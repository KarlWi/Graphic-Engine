#include "camera.h"

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

camera::camera(){

}

camera::camera(glm::mat4 proj2, glm::mat4 view2){
	camera::proj;
	camera::view;
	proj = proj2;
	view = view2;

}

void camera::configCamera(float z){
	camera::proj;
	camera::view;
	proj = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 50.0f);//Define la matriz de proyección
	view[3].z = z;
}
