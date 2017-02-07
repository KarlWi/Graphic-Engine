#ifndef _object_H
#define _object_H
#include "BOX.h"
#include "program.h"

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

class object{
public:
	glm::mat4 model;
	unsigned int vao;

	unsigned int inPos;
	unsigned int inColor;
	unsigned int inNormal;

	unsigned int posVBO;
	unsigned int colorVBO;
	unsigned int normalVBO;
	unsigned int triangleIndexVBO;

	float angle;

	unsigned int Ka;
	unsigned int Kd;
	unsigned int Ks;
	unsigned int alpha;

	
	program prog;

	object(glm::mat4 mod,program prog);//constructor dependiende de la matriz model
	//PREGUNTA PARA MARCOS: Que significa el 1 n glgenvertexarray?
	void setVao();//Generamos el vao del objeto creado
	void setVbo(program prog);//
	//Función para crear los vbo de cada atributo.
		//vboName: Nombre del vbo (en función del atributo), posVBO, colorVBO...
		//inAttribute: Atributo de entrada (inPos, inNormal...).
		//cubeVertexData: Matriz de cada uno de los atributos (matriz de normales, de posición...). Está en BOX o en el archivo de objeto correspondiente.
		//nVertex: Numero de vertices del objeto.
	object();

	void setMaterialProp(float ambiental, float diffuse, float specular, float N);

	void rotate();

};

#endif