#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

in vec3 Normal;
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;

uniform sampler2D tex1;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;


void main()
{
	float ambientLight = 0.28f;
	
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);

	float diffuseLight = max(dot(normal, lightDirection), 0.0f);

	float specular = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos); 
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection,reflectionDirection), 0.0f), 8);
	float specularLight = specAmount * specular;
	
	FragColor = texture(tex0, texCoord) * lightColor * (diffuseLight + ambientLight) + texture(tex1, texCoord).r * specularLight; 
}