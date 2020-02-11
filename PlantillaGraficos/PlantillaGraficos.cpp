// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <math.h>

#include <iostream>

using namespace std;

//Declarar una ventana
GLFWwindow* window;
float posXTriangulo = 0.0f , posYTriangulo = 0.0f;

float posXCuadrado = 0.5f, posYCuadrado = 0.5f;

double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 0.8;

void teclado_callback(GLFWwindow* window,
	int key, int scancode, int action, int mods) {

	if (
		(action == GLFW_PRESS || action == GLFW_REPEAT) 
		&& key == GLFW_KEY_RIGHT) {
		posXTriangulo += 0.01;
	}

	if (
		(action == GLFW_PRESS || action == GLFW_REPEAT)
		&& key == GLFW_KEY_LEFT) {
		posXTriangulo -= 0.01;
	}

	if (
		(action == GLFW_PRESS || action == GLFW_REPEAT)
		&& key == GLFW_KEY_UP) {
		posYTriangulo += 0.01;
	}

	if (
		(action == GLFW_PRESS || action == GLFW_REPEAT)
		&& key == GLFW_KEY_DOWN) {
		posYTriangulo -= 0.01;
	}



}

void actualizar() {
	tiempoActual = glfwGetTime();
	double tiempoDiferencial = 
		tiempoActual - tiempoAnterior;
	int estadoDerecha =
		glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		posXTriangulo += velocidadTriangulo * tiempoDiferencial;
	}
	int estadoArriba =
		glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		posYTriangulo += velocidadTriangulo * tiempoDiferencial;
	}
	int estadoIzquierda =
		glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		posXTriangulo -= velocidadTriangulo * tiempoDiferencial;
	}
	int estadoAbajo =
		glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS) {
		posYTriangulo -= velocidadTriangulo * tiempoDiferencial;
	}

	tiempoAnterior = tiempoActual;
}

void dibujarTriangulo() {
	glPushMatrix();

	glTranslatef(posXTriangulo, posYTriangulo, 0.0f);

	glBegin(GL_TRIANGLES);

	glColor3f(0.2, 0.6, 0.1);
	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);

	glEnd();
	glPopMatrix();
}

void dibujarCuadrado() {
	glPushMatrix();

	glTranslatef(posXCuadrado, posYCuadrado, 0.0f);

	glBegin(GL_QUADS);

	glColor3f(0.7, 0.2, 0.5);
	glVertex3f(-0.15f, 0.15f, 0.0f);
	glVertex3f(0.15f, 0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);

	glEnd();
	glPopMatrix();
}

void dibujar() {
	dibujarTriangulo();
	dibujarCuadrado();

	
}

int main()
{
    

	//Si no se pudo iniciar GLFW
	//Terminamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//inicializamos la ventana
	window =
		glfwCreateWindow(600, 600, "Ventana",
			NULL, NULL);
	//Si no se pudo crear la venata
	//Terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto
	//Se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK) {
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL =
		glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//Establecemos que con cada evento de teclado
	//se llama a la función teclado_callback
	//glfwSetKeyCallback(window, teclado_callback);

	tiempoActual = glfwGetTime();
	tiempoAnterior = tiempoActual;
	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 600, 600);
		//Establecemos el color de borrado
		//Valores RGBA
		glClearColor(1, 0.8, 0, 1);
		//Borrar!
		glClear(GL_COLOR_BUFFER_BIT | 
			GL_DEPTH_BUFFER_BIT);

		//Actualizar valores y dibujar
		actualizar();
		dibujar();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//Despúes del ciclo de dibujo
	//Eliminamos venta y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}
