#include"shaderClass.h"

// Lê um arquivo de texto e da como output todo o texto nele contido
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Construtor
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Lê e armazena as strings do vertex e fragment shader
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Converte as strings recebidas em arrays de caracteres
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Cria o Vertex Shader Object e sua referencia
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Conecta o vertex shader source e o vertex shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compila o Vertex Shader para linguagem de máquina 
	glCompileShader(vertexShader);
	// Verifica a compilação 
	compileErrors(vertexShader, "VERTEX");

	// Cria o Fragment Shader Object e sua referência
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Conecta o fragment shader source e o fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compila o fragment shade para linguagem de máquina
	glCompileShader(fragmentShader);
	// Verifica a compilação
	compileErrors(fragmentShader, "FRAGMENT");

	// Cria o Shader Program e sua referência
	ID = glCreateProgram();
	// Linka o fragment e o vertex shader ao Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Concluindo o link
	glLinkProgram(ID);
	// Verifica o se o link entre os shaders ocorreu corretamente
	compileErrors(ID, "PROGRAM");

	// Deleta o Fragment e Vertex shader objects que agora já não são mais úteis
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Armazena o status de compilação
	GLint hasCompiled;
	// Array de caracteres para armazenar eventual mensagem de erro
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}