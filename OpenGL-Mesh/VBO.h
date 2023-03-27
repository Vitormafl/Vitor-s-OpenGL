#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include<glad/glad.h>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
public:
	// ID de referência para o VBO 
	GLuint ID;
	// Construtor que gera o VBO e faz o link com os vértices
	VBO(std::vector<Vertex>& vertices);

	// Vincula o VBO
	void Bind();
	// Desvincula o VBO
	void Unbind();
	// Deleta o VBO
	void Delete();
};

#endif