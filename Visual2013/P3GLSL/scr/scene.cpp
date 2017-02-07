#include "BOX.h"

#include "scene.h"
#include "camera.h"
#include "object.h"
#include "program.h"

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

scene::scene(){
	nDirectionalLightValue = 0;
	nPointLightValue = 0;
	nFocalLightValue = 0;
	nObjects = 0;
	glm::vec3 ceros = glm::vec3(0.0,0.0,0.0);
	for (int i = 0; i < 8;i++){

		directionalLightIntensityValue[i] = ceros;
		directionalLightDirValue[i] = ceros;

		pointLightIntensityValue[i] = ceros;
		pointLightPosValue[i] = ceros;

		focalLightIntensityValue[i] = ceros;
		focalLightDirValue[i] = ceros;
		focalLightPosValue[i] = ceros;
		focalLightApertureValue[i] = 0.0f;
	}
	
}

void scene::setCamera(camera cm){
	scene::cam = cm;
}

void scene::setDirLight(glm::vec3 intensity, glm::vec3 direction){
	
	directionalLightIntensityValue[nDirectionalLightValue] = intensity;
	directionalLightDirValue[nDirectionalLightValue] = direction;
	nDirectionalLightValue++;
	
}

void scene::setPointLight(glm::vec3 intensity, glm::vec3  pos){
	
	pointLightIntensityValue[nPointLightValue] = intensity;
	pointLightPosValue[nPointLightValue] = pos;
	nPointLightValue++;
	//pointLightPos = glGetUniformLocation(prog.prog, "lpos");
	//glUniform3f(pointLightPos, pos.x, pos.y, pos.z);
	//pointLightIntensity = glGetUniformLocation(prog.prog, "I");
	//glUniform3f(pointLightIntensity, intensity.x,intensity.y,intensity.z);
	
}

void scene::setAmbientLight(glm::vec3 intensity){
	ambientLightValue = intensity;
	
}

 void scene::setFocalLight(glm::vec3 intensity, glm::vec3 dir, glm::vec3  pos, float aperture){
	 focalLightIntensityValue[nFocalLightValue] = intensity;
	 focalLightDirValue[nFocalLightValue] = dir;
	 focalLightPosValue[nFocalLightValue] = pos;
	 focalLightApertureValue[nFocalLightValue] = aperture;
	 nFocalLightValue++;

}

 void scene::setObject(glm::mat4 model, program p, float Kambiental, float Kdiffuse, float Kspecular, float alpha){
	objs[nObjects] = object(model,p);
	objs[nObjects].setVao();
	objs[nObjects].setVbo(p);
	
	objsKa[nObjects] = Kambiental;
	objsKd[nObjects] = Kdiffuse;
	objsKs[nObjects] = Kspecular;
	objsAlpha[nObjects] = alpha;
	nObjects++;
}

void scene::render(){
	


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Limpia el buffer de color y profundidad

	for (int i = 0; i < nObjects; i++){
		objs[i].setMaterialProp(objsKa[i], objsKd[i], objsKs[i], objsAlpha[i]);
		//LUZ AMBIENTAL
		ambientLight = glGetUniformLocation(objs[i].prog.prog, "Ia");
		glUniform3f(ambientLight, ambientLightValue.x, ambientLightValue.y, ambientLightValue.z);

		//LUZ DIRECCIONAL
		directionalLightIntensity = glGetUniformLocation(objs[i].prog.prog, "directionalLightIntensity");
		directionalLightDir = glGetUniformLocation(objs[i].prog.prog, "directionalLightDir");
		nDirectionalLight = glGetUniformLocation(objs[i].prog.prog, "nDirectionalLight");

		glUniform1i(nDirectionalLight, nDirectionalLightValue);
		glUniform3fv(directionalLightIntensity, 8, &directionalLightIntensityValue[0][0]);
		glUniform3fv(directionalLightDir, 8, &directionalLightDirValue[0][0]);


		//LUZ PUNTUAL
		pointLightIntensity = glGetUniformLocation(objs[i].prog.prog, "pointLightIntensity");
		pointLightPos = glGetUniformLocation(objs[i].prog.prog, "pointLightPos");
		nPointLight = glGetUniformLocation(objs[i].prog.prog, "nPointLight");

		glUniform1i(nPointLight, nPointLightValue);
		glUniform3fv(pointLightIntensity, 8, &pointLightIntensityValue[0][0]);
		glUniform3fv(pointLightPos, 8, &pointLightPosValue[0][0]);

		//LUZ FOCAL

		focalLightIntensity = glGetUniformLocation(objs[i].prog.prog, "focalLightIntensity");
		focalLightPos = glGetUniformLocation(objs[i].prog.prog, "focalLightPos");
		focalLightDir = glGetUniformLocation(objs[i].prog.prog, "focalLightDir");
		focalLightAperture = glGetUniformLocation(objs[i].prog.prog, "focalLightAperture");
		nFocalLight = glGetUniformLocation(objs[i].prog.prog, "nFocalLight");

		glUniform1i(nFocalLight, nFocalLightValue);
		glUniform3fv(focalLightIntensity, 8, &focalLightIntensityValue[0][0]);
		glUniform3fv(focalLightPos, 8, &focalLightPosValue[0][0]);
		glUniform3fv(focalLightDir, 8, &focalLightDirValue[0][0]);
		glUniform1fv(focalLightAperture, 8, &focalLightApertureValue[0]);







		

		glUseProgram(objs[i].prog.prog);

		glm::mat4 modelView = cam.view * objs[i].model;//Se definen las combinaciones de matrices
		glm::mat4 modelViewProj = cam.proj * cam.view * objs[i].model;//Se definen las combinaciones de matrices
		glm::mat4 normal = glm::transpose(glm::inverse(modelView));

		unsigned int uModelViewMat;
		unsigned int uModelViewProjMat;
		unsigned int uNormalMat;
		uNormalMat = glGetUniformLocation(objs[i].prog.prog, "normal");
		uModelViewMat = glGetUniformLocation(objs[i].prog.prog, "modelView");
		uModelViewProjMat = glGetUniformLocation(objs[i].prog.prog, "modelViewProj");

		if (uModelViewMat != -1)
			glUniformMatrix4fv(uModelViewMat, 1, GL_FALSE,//(Variable uniforme, número de matrices,es transpuesta?, puntero al array de valores)
			&(modelView[0][0]));
		//std::cout << "modelviewmat" << uModelViewMat << std::endl;
		if (uModelViewProjMat != -1)
			glUniformMatrix4fv(uModelViewProjMat, 1, GL_FALSE,
			&(modelViewProj[0][0]));
		//std::cout << "modelviewprojmat" << uModelViewProjMat << std::endl;
		if (uNormalMat != -1)
			glUniformMatrix4fv(uNormalMat, 1, GL_FALSE,
			&(normal[0][0]));
		//std::cout << "normalmat" << uNormalMat << std::endl;

		glDrawElements(GL_TRIANGLES, cubeNTriangleIndex * 3, //(Primitivas, número de primitivas, formato de indices, puntero hacia datos ya puestos)
			GL_UNSIGNED_INT, (void*)0);	
	
		if (rotate == true){
			objs[i].rotate();
		}
	
	
	}
	
	glutSwapBuffers();
}

void scene::destroyScene(){
	for (int i = 0; i < nObjects; i++){

		glDetachShader(objs[i].prog.prog, objs[i].prog.vshader);
		glDetachShader(objs[i].prog.prog, objs[i].prog.fshader);
		glDeleteShader(objs[i].prog.vshader);
		glDeleteShader(objs[i].prog.fshader);
		glDeleteProgram(objs[i].prog.prog);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		if (objs[i].inPos != -1) glDeleteBuffers(1, &objs[i].posVBO);
		if (objs[i].inColor != -1) glDeleteBuffers(1, &objs[i].colorVBO);
		if (objs[i].inNormal != -1) glDeleteBuffers(1, &objs[i].normalVBO);
		glDeleteBuffers(1, &objs[i].triangleIndexVBO);
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &objs[i].vao);
	}

}