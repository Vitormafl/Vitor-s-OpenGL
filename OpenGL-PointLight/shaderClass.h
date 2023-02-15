#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	//ID do Shader Program
	GLuint ID;
	//Construtor para o Shader Program a partir do VertexShader e do FragmentShader
	Shader(const char* vertexFile, const char* fragmentFile);

	//Ativa o Shader Program
	void Activate();
	//Deleta o Shader Program
	void Delete();

private:
	//Verifica se todos os shaders compilaram propriamente
	void compileErrors(unsigned int shader, const char* type);
};

#endif