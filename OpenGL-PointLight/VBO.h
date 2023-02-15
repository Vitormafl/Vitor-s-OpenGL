#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	// ID de refer�ncia para o VBO 
	GLuint ID;
	// Construtor que gera o VBO e faz o link com os v�rtices
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Vincula o VBO
	void Bind();
	// Desvincula o VBO
	void Unbind();
	// Deleta o VBO
	void Delete();
};

#endif