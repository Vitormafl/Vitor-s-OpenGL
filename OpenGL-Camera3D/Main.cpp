#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"



const unsigned int width = 800;
const unsigned int height = 800;



// Coordenadas
GLfloat vertices[] =
{ //     COORDENADAS     /        CORES           /   TexCoords  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices para ordem dos vertices
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


int main()
{
	//inicializar o GLFW
	glfwInit();

	//Passar a versão que estamos usando do openGL, no caso 3.3	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//O openGL possui diversos perfis, como o legacy e o core, nesse caso estamos usando o CORE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Criar janela passando dados de altura e largura e o nome da janela
	GLFWwindow* window = glfwCreateWindow(width, height, "Vitor openGL", NULL, NULL);

	//Caso de teste para erros na criação da janela
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//colocar a janela criada no contexto a ser utilizado
	glfwMakeContextCurrent(window);

	//utilizar a biblioteca glad para configurar o openGL
	gladLoadGL();
	//especificar a porção de visualização dos eixos x e y da janela, nesse caso, de 0 a 800
	glViewport(0, 0, width, height);

	//inicializa o objeto de shader usando os shaders default shader e fragment shader
	Shader shaderProgram("default.vert", "default.frag");

	//Criar o vertex array object e bindá-lo
	VAO VAO1;
	VAO1.Bind();

	//Criar o vertex buffer object e linká-lo aos vertices
	VBO VBO1(vertices, sizeof(vertices));
	//Criar o element buffer object e linká-lo aos indices
	EBO EBO1(indices, sizeof(indices));

	//Fazer o link dos atributos do VBO, como cor e coordenadas para o VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	//Desvincular todos os objetos para garantir que eles não sejam modificador por acidente
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Criar a textura 
	Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	//Corrigir erro de interceção onde objetos atrás de outros aparecem como se estivessem na frente
	glEnable(GL_DEPTH_TEST);

	//Inicializando camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//While loop principal 
	while (!glfwWindowShouldClose(window))
	{
		//passar a cor de fundo
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//limpar o color buffer e o depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//passar para o openGL qual programa de shader vamos utilizar
		shaderProgram.Activate();

		//tratar as entradas de camera (movimentação, olhar, etc.)
		camera.Inputs(window);
		//atualiza e exporta a matriz da camera para o vertex shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		//vincular a textura
		brickTex.Bind();

		//vincula o VAO
		VAO1.Bind();
		//desenha as primitivas e passa informações como numero de indices, tipo de dado, etc.
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		//troca o back buffer com o front buffer 
		glfwSwapBuffers(window);
		//trata todos os eventos do glfw
		glfwPollEvents();
	}

	//Deleta todos so objetos que foram criados para liberar a memória
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	//Deleta a janela antes de encerrar o programa 
	glfwDestroyWindow(window);
	//Encerra o GLFW antes de encerrar o programa
	glfwTerminate();
	return 0;
}