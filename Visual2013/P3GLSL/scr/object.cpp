#include "BOX.h"
#include "object.h"
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

object::object(glm::mat4 mod,program prog){
	object::model = mod;
	object::prog = prog;
	angle=0.01;
}
object::object(){}

void object::setVao(){
	glGenVertexArrays(1, &vao);//Creamos un vao
	glBindVertexArray(vao);//Activamos el vao
}
void object::setVbo(program prog){
	glBindAttribLocation(prog.prog, 0, "inPos");
	glBindAttribLocation(prog.prog, 1,"inColor");
	glBindAttribLocation(prog.prog,2, "inNormal");

	inPos = glGetAttribLocation(prog.prog,"inPos");

	inColor = glGetAttribLocation(prog.prog, "inColor");

	inNormal = glGetAttribLocation(prog.prog, "inNormal");
	
	

	if (inPos != -1)
	{
		//std::cout << "Asereje" << std::endl;
		glGenBuffers(1, &posVBO);//Numero de buffers a crear y variable para meterlo.
		//std::cout << "ja" << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, posVBO);//Se enlaza el buffer.
		//std::cout << "de" << std::endl;
		glBufferData(GL_ARRAY_BUFFER, cubeNVertex*sizeof(float) * 3,
			cubeVertexPos, GL_STATIC_DRAW);//Subimos los datos.
		//std::cout << "je" << std::endl;
		glVertexAttribPointer(inPos, 3, GL_FLOAT, GL_FALSE, 0, 0);//Indico identificador para el shader.
		//std::cout << "lerele" << std::endl;
		glEnableVertexAttribArray(inPos);//Activamos el atributo correspondiente.
	}
	if (inColor != -1)
	{
		//std::cout << "Asereje" << std::endl;
		glGenBuffers(1, &colorVBO);//Numero de buffers a crear y variable para meterlo.
		//std::cout << "ja" << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);//Se enlaza el buffer.
		//std::cout << "de" << std::endl;
		glBufferData(GL_ARRAY_BUFFER, cubeNVertex*sizeof(float) * 3,
			cubeVertexColor, GL_STATIC_DRAW);//Subimos los datos.
		//std::cout << "je" << std::endl;
		glVertexAttribPointer(inColor, 3, GL_FLOAT, GL_FALSE, 0, 0);//Indico identificador para el shader.
		//std::cout << "lerele" << std::endl;
		glEnableVertexAttribArray(inColor);//Activamos el atributo correspondiente.
	}

	if (inNormal != -1)
	{
		//std::cout << "Asereje" << std::endl;
		glGenBuffers(1, &normalVBO);//Numero de buffers a crear y variable para meterlo.
		//std::cout << "ja" << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);//Se enlaza el buffer.
		//std::cout << "de" << std::endl;
		glBufferData(GL_ARRAY_BUFFER, cubeNVertex*sizeof(float) * 3,
			cubeVertexNormal, GL_STATIC_DRAW);//Subimos los datos.
		//std::cout << "je" << std::endl;
		glVertexAttribPointer(inNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);//Indico identificador para el shader.
		//std::cout << "lerele" << std::endl;
		glEnableVertexAttribArray(inNormal);//Activamos el atributo correspondiente.
	}

	glGenBuffers(1, &triangleIndexVBO);
	//std::cout << "triangleindex"<<triangleIndexVBO << std::endl;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIndexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		cubeNTriangleIndex*sizeof(unsigned int) * 3, cubeTriangleIndex,
		GL_STATIC_DRAW);
}

void object::rotate(){
	angle = (angle > 3.141592f * 2.0f) ? 0 : angle + 0.0000001f;
	model = glm::rotate(model, angle, glm::vec3(1.0f, 1.0f, 0.0f));
	glutPostRedisplay();//Lanza un evento de renderizado
}

void object::setMaterialProp(float ambiental, float diffuse, float specular, float alphaC){
	Ka = glGetUniformLocation(prog.prog, "Ka");
	Kd = glGetUniformLocation(prog.prog, "Kd");
	Ks = glGetUniformLocation(prog.prog, "Ks");
	alpha = glGetUniformLocation(prog.prog, "alpha");


	if (Ka != -1){
		glUniform1f(Ka,ambiental);
	}
	if (Kd != -1){
		glUniform1f(Kd, diffuse);
	}
	if (Ks != -1){
		glUniform1f(Ks, specular);
	}
	if (alpha != -1){
		glUniform1f(alpha, alphaC);
	}


}
