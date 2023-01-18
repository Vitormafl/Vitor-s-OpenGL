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


	//Declarando os vértices
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

	//criar  o objeto vertexShader e sua referencia
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//linkar o source o vertex shader com o objeto criado vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compilar o vertex shader para codigo de maquina
	glCompileShader(vertexShader);

	//repetir o mesmo processo do vertexShader para o fragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//criar objeto shader program e pegar sua referencia
	GLuint shaderProgram = glCreateProgram();

	//conectar o vertex e o fragment shader ao shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//terminando de linkar todos os shaders ao programa
	glLinkProgram(shaderProgram);

	//como os shaders já foram passados ao programa, eles passam a ser inuteis, logo vamos deleta-los
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//criar containers de referencia para o Vertex Array Object (VAO) e para o Vertex Buffer Object (VBO)
	GLuint VAO, VBO;

	//gerar o VAO e VBO, ambos com 1 objeto
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Tornar o VAO o Vertex Array Object padrao do GL usando função de bind
	glBindVertexArray(VAO);

	//Bindando o VBO, especificando que ele é um GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Passar os vértices para o VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configurar os atributos de vértice para que o OpenGL leia o VBO corretamente
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//habilitar o VertexAttribute para que o OpenGL saiba utiliza-lo
	glEnableVertexAttribArray(0);

	//Bindar o VBO e o VAO para 0, para não modificar acidentalmente o VBO e VAO que criamos acima
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
		//cor de fundo
		glClearColor(0.9f, 0.93f, 0.17f, 1.0f);
		//limpar o back buffer e passar sua nova cor
		glClear(GL_COLOR_BUFFER_BIT);
		//passar para o OpenGL o programa de shader que queremos utilizar
		glUseProgram(shaderProgram);
		//bindar o VAO
		glBindVertexArray(VAO);
		//Desenhar o triangulo usando a primitiva GL_TRIANGLES
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//trocar o back buffer com o front buffer
		glfwSwapBuffers(window);

		//lidar com todos os eventos do glfw
		glfwPollEvents();
	}

	//deletando todos os objetos que foram criados
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//encerrar o programa, matando a janela e terminando o glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
