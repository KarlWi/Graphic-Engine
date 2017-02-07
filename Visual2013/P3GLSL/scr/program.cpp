#include "BOX.h"
#include "program.h"
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

GLuint program::loadShader(const char *fileName, GLenum type){
	//std::cout << "sevilla" << std::endl;
	unsigned int fileLen;//Longitud de caracteres del archivo
	char *source = loadStringFromFile(fileName, fileLen);//Carga el string del archivo
	//std::cout << "tiene" << std::endl;
	//////////////////////////////////////////////
	//Creación y compilación del Shader
	GLuint shader;//Identificador del shader
	//std::cout << "un" << std::endl;
	shader = glCreateShader(type);//Tipo de shader creado
	//std::cout << "color" << std::endl;
	glShaderSource(shader, 1,
		(const GLchar **)&source, (const GLint *)&fileLen);//Fuente del shader
	//std::cout << "especial" << std::endl;
	glCompileShader(shader);//Compila el shader para comprobar que está correcto
	delete source;
	
	//Comprobamos que se compiló bien
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		//Calculamos una cadena de error
		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		char *logString = new char[logLen];
		glGetShaderInfoLog(shader, logLen, NULL, logString);
		std::cout << "filename " << fileName << std::endl;
		std::cout << "Error: " << logString << std::endl;
		delete logString;
		glDeleteShader(shader);
		exit(-1);
	}
	return shader;//Devuelve el ID del shader compilado
	//std::cout << "un color especial" << std::endl;
}
program::program(const char *vertexAddress, const char *fragAddress){
	//std::cout << "Murcia" << std::endl;
	program::vshader = program::loadShader(vertexAddress, GL_VERTEX_SHADER);//Carga el shader de vértices
	program::fshader = program::loadShader(fragAddress, GL_FRAGMENT_SHADER);//Carga el shader de fragmentos
	//std::cout << "que hermosa eres" << std::endl;

	program::prog = glCreateProgram();//Crea el progrma
	glAttachShader(program::prog, program::vshader);//Enlaza el vshader al programa
	glAttachShader(program::prog, program::fshader);//Enlaza el fshader al programa

	glLinkProgram(program::prog);//Enlaza el programa


	//Comprueba error en la fase de enlazado
	int linked;
	glGetProgramiv(program::prog, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		//Calculamos una cadena de error
		GLint logLen;
		glGetProgramiv(program::prog, GL_INFO_LOG_LENGTH, &logLen);
		char *logString = new char[logLen];
		glGetProgramInfoLog(program::prog, logLen, NULL, logString);
		std::cout << "Error: " << logString << std::endl;
		delete logString;
		glDeleteProgram(program::prog);
		program::prog = 0;
		exit(-1);
	}

}
program::program(){};