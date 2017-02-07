#include "BOX.h"
#include "auxiliar.h"
#include "camera.h"
#include "attributes.h"
#include "uniforms.h"
#include "object.h"
#include "program.h"
#include "scene.h"

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



//////////////////////////////////////////////////////////////
// Datos que se almacenan en la memoria de la CPU
//////////////////////////////////////////////////////////////

//Matrices
glm::mat4	proj = glm::mat4(1.0f);
glm::mat4	view = glm::mat4(1.0f);
glm::mat4	model1 = glm::mat4(1.0f);
glm::mat4	model2 = glm::mat4(1.0f);



//////////////////////////////////////////////////////////////
// Variables que nos dan acceso a Objetos OpenGL
//////////////////////////////////////////////////////////////
//Por definir

program *p1 = nullptr;
program *p2 = nullptr;
camera *cam = nullptr;
scene *s1 = nullptr;



//////////////////////////////////////////////////////////////
// Funciones auxiliares
//////////////////////////////////////////////////////////////
//!!Por implementar

//Declaración de CB
void renderFunc();
void resizeFunc(int width, int height);
void idleFunc();
//void keyboardFunc(unsigned char key, int x, int y);
//void mouseFunc(int button, int state, int x, int y);
//void renderCube();
void cargaAtributos();

//Funciones de inicialización y destrucción
void initContext(int argc, char** argv);
void initOGL();
void initShader(const char *vname, const char *fname);
void initObj();
void destroy();


//Carga el shader indicado, devuele el ID del shader
//!Por implementar
//GLuint loadShader(const char *fileName, GLenum type);

//Crea una textura, la configura, la sube a OpenGL, 
//y devuelve el identificador de la textura 
//!!Por implementar
//unsigned int loadTex(const char *fileName);


int main(int argc, char** argv)
{
	std::locale::global(std::locale("spanish"));// acentos ;)
	
	
	initContext(argc, argv);
	//Creamos dos programas que se llaman diferente
	p1 = new program("../shaders_P3/shader.v0.vert", "../shaders_P3/shader.v0.frag");
	p2 = new program("../shaders_P3/shader.v3.vert", "../shaders_P3/shader.v3.frag");
	//Creamos una escena
	s1 = new scene();
	//Inicializamos
	initOGL();
	//Creamos una camara
	cam = new camera(proj, view);
	cam->configCamera(0.0f);
	//Colocamos la camara en la escena
	s1->setCamera(*cam);

	//Colocamos un objeto en la escena
	model1[3].z = -10.0f;
	model1[3].y = -3.0f;
	//La funcion setObject tiene como parametros la posicion, el programa, y los parametros del material (Ka,Kd,Ks y alpha)
	s1->setObject(model1,*p1,1.0f,1.0f,1.0f,1.0f);

	//Colocamos otro objeto en la escena
	model2[3].z = -10.0f;
	model2[3].y = 3.0f;
	//La funcion setObject tiene como parametros la posicion, el programa, y los parametros del material (Ka,Kd,Ks y alpha)
	s1->setObject(model2, *p1, 0.0f, 0.0f, 0.5f, 0.5f);

	//Colocamos un tercer objeto en la escena
	model2[3].y = 0.0f;
	//La funcion setObject tiene como parametros la posicion, el programa, y los parametros del material (Ka,Kd,Ks y alpha)
	s1->setObject(model2, *p1, 0.3f, 0.3f, 0.3f, 0.3f);
	

	//Decimos a la escena que roten los cubos
	s1->rotate = true;


	//Aquí ponemos ejemplos para activar y desactivar diferentes luces, en funcion de los diferentes parametros


	s1->setAmbientLight(glm::vec3(1.0f,1.0f,1.0f));
	//s1->setDirLight(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	s1->setDirLight(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	//s1->setPointLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 00.0f));
	//s1->setPointLight(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-5.0f, 0.0f, 10.0f));
	//s1->setFocalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f),0.1f);
	//Añade el bucle de eventos


	glutMainLoop();
	
	destroy();

	//return 0;

	
}
	
//////////////////////////////////////////
// Funciones auxiliares 
void initContext(int argc, char** argv){
	glutInit(&argc, argv);//Inicializa
	glutInitContextVersion(3, 3);//Mete la versión de OpenGl
	glutInitContextProfile(GLUT_CORE_PROFILE);//Inicializa el perfil del contexto

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);//Define el Frame Buffer
	glutInitWindowSize(500, 500);//Define tamaño de la ventana
	glutInitWindowPosition(0, 0);//DEfine la posición donde empieza
	glutCreateWindow("Prácticas GLSL");//Nombre de la ventana

	glewExperimental = GL_TRUE;//Inicializa las extensiones
	GLenum err = glewInit();
	//Comprobación para errores
	if (GLEW_OK != err)
	{
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		exit(-1);
	}
	//Comprobación de la compatibilidad del equipo
	const GLubyte *oglVersion = glGetString(GL_VERSION);
	std::cout << "This system supports OpenGL Version: " << oglVersion << std::endl;


	//Se indican las funciones que tratarán los diferentes eventos
	glutReshapeFunc(resizeFunc);
	glutDisplayFunc(renderFunc);
	glutIdleFunc(idleFunc);
	//glutKeyboardFunc(keyboardFunc);
	//glutMouseFunc(mouseFunc);



}
void initOGL(){
	glEnable(GL_DEPTH_TEST);//Activa el test de profundidad
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);//Establece el color de fondo

	glFrontFace(GL_CCW);//Indica la orientación de la cara front (Counter Clock-Wise)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Especifica cómo será rasterizado el polígono
	glEnable(GL_CULL_FACE);//Activa el culling

	//proj = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 50.0f);//Define la matriz de proyección
	//view = glm::mat4(1.0f);//Define la matriz de vista
	//view[3].z = -6;//Pone la cámara en z = -6
	

}
void destroy(){
	s1->destroyScene();

}


/*GLuint loadShader(const char *fileName, GLenum type){ 
	unsigned int fileLen;//Longitud de caracteres del archivo
	char *source = loadStringFromFile(fileName, fileLen);//Carga el string del archivo
	//////////////////////////////////////////////
	//Creación y compilación del Shader
	GLuint shader;//Identificador del shader
	shader = glCreateShader(type);//Tipo de shader creado
	glShaderSource(shader, 1,
		(const GLchar **)&source, (const GLint *)&fileLen);//Fuente del shader
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
}*/
/*unsigned int loadTex(const char *fileName){
	//A partir del nombre de archivo carga una textura
	unsigned char *map;
	unsigned int w, h;//anchura y altura
	map = loadTexture(fileName, w, h);//se crea la textura
	if (!map)
	{
		std::cout << "Error cargando el fichero: "
			<< fileName << std::endl;
		exit(-1);
	}
	unsigned int texId;
	glGenTextures(1, &texId);//Se crea el que será el identificador de la textura
	glBindTexture(GL_TEXTURE_2D, texId);//Se activa la textura como una textura 2D
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA,//(Tipo de textura, nivel de detalle, formato interno, anchura texels, altura texels,0,formato de pixel,
		GL_UNSIGNED_BYTE, (GLvoid*)map);//tipo de dato del pixel, puntero a la imagen en memoria
	delete[] map;
	glGenerateMipmap(GL_TEXTURE_2D);//Generamos el mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,//(Tipo de textura, nombre simbólico, tipo de ajuste al objeto)
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);



	return texId;
}*/

void renderFunc(){
	s1->render();

}


void resizeFunc(int width, int height){
	glViewport(0, 0, width, height);
}
void idleFunc(){

}
/*void keyboardFunc(unsigned char key, int x, int y)*/
/*void mouseFunc(int button, int state, int x, int y){}*/









