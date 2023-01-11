#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() 
{
	//inicializando o openGL
	glfwInit();

	//Passando para o glfw qual versao do openGL sera utilizada
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3 , 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3 , 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3 , 0.0f,
	};
	
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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	//Definindo uma cor de background para a janela
	glClearColor(0.9f, 0.93f, 0.17f, 1.0f);
	//Limpar o back buffer para utilizar em seguida
	glClear(GL_COLOR_BUFFER_BIT);
	//trocar o front buffer pelo back buffer
	glfwSwapBuffers(window);

	//loop para garantir que a janela nao ira fechar instantaneamente
	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.9f, 0.93f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//encerrar o programa, matando a janela e terminando o glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}