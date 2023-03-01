#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID de referência para o VAO
	GLuint ID;
	// Construtor para gerar o VAO ID
	VAO();

	// Faz o link de um atributo do VBO, como cores ou posições para o VAO 
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Vincula o VAO
	void Bind();
	// desvincula o VAO
	void Unbind();
	// Deleta o VAO
	void Delete();
};

#endif