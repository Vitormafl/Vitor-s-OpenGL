#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() 
{
	//inicializando o openGL
	glfwInit();

	//Passando para o glfw qual versao do openGL sera utilizada
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Comando para criar a janela a ser utilizada
	GLFWwindow* window = glfwCreateWindow(800,800,"Vitor's OpenGL project", NULL, NULL);

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
	
	//Definindo uma cor de background para a janela
	glClearColor(0.9f, 0.93f, 0.17f, 1.0f);
	//Limpar o back buffer para utilizar em seguida
	glClear(GL_COLOR_BUFFER_BIT);
	//trocar o front buffer pelo back buffer
	glfwSwapBuffers(window);

	//loop para garantir que a janela nao ira fechar instantaneamente
	while (!glfwWindowShouldClose(window)) 
	{
		glfwPollEvents();
	}

	//encerrar o programa, matando a janela e terminando o glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}