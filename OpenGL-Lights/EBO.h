#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
public:
	// ID do EBO (Elements Buffer Object)
 	GLuint ID;
	// Construtor para o EBO, fazendo o link com os indices 
	EBO(GLuint* indices, GLsizeiptr size);

	//Vincula o EBO
	void Bind();
	//Desvincula o EBO
	void Unbind();
	//Delte o EBO
	void Delete();
};

#endif