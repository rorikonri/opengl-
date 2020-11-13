#version 330 core   

layout(location = 0) in vec3 aPos;              
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

//out vec3 ourColor; 
//out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;


void main(){                                    
		
		FragPos = vec3(modelMat * vec4(aPos, 1.0));
		gl_Position = projMat * viewMat * vec4(aPos, 1.0);
		Normal = mat3(modelMat) * aNormal;
		TexCoord = aTexCoord;
		//ourColor = aColor;
		//TexCoord = aTexCoord;
}                             