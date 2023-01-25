#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


//Declarando os vértices
GLfloat vertices[] =
{ //               COORDENADAS           /           CORES           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f,
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f,
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f,
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, 
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, 
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  
};

// Indices para ordem dos vertices 
GLuint indices[] =
{
	0, 3, 5, // triangulo inferior esquerdo
	3, 2, 4, // triangulo inferior direito
	5, 4, 1 // triangulo superior central
};


int main()
{
	//inicializando o openGL
	glfwInit();

	//Passando para o glfw qual versao do openGL sera utilizada
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Comando para criar a janela a ser utilizada
	GLFWwindow* window = glfwCreateWindow(800, 800, "Vitor's OpenGL project", NULL, NULL);

	//Checagem de erros na criacao da janela
	if (window == NULL)
	{
		std::cout << "falha na criacao da janela GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}

	//passando a janela para o "contexto" do glfw
	glfwMakeContextCurrent(window);

	//utilizando o glad para configurar o OpenGL
	gladLoadGL();

	//especificar como iremos percorrer os pixeis da janela, nesse caso, de x = 0 e y = 0 para x = 800 e y = 800
	glViewport(0, 0, 800, 800);


	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//loop para garantir que a janela nao ira fechar instantaneamente
	while (!glfwWindowShouldClose(window))
	{
		//cor de fundo
		glClearColor(0.9f, 0.93f, 0.17f, 1.0f);
		//limpar o back buffer e passar sua nova cor
		glClear(GL_COLOR_BUFFER_BIT);
		//passar para o OpenGL o programa de shader que queremos utilizar
		shaderProgram.Activate();

		glUniform1f(uniID, 0.5f);
		//bindar o VAO
		VAO1.Bind();
		//Desenhar os triangulos usando a primitiva GL_TRIANGLES, usando funcao glDrawElements
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//trocar o back buffer com o front buffer
		glfwSwapBuffers(window);

		//lidar com todos os eventos do glfw
		glfwPollEvents();
	}

	//deletando todos os objetos que foram criados
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//encerrar o programa, matando a janela e terminando o glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}