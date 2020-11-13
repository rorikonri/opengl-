#version 330 core                        

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

out vec4 FragColor;   

uniform Material material;
//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 cameraPos;

void main(){    
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 reflectVec = reflect(-lightDir, Normal);
    vec3 cameraVec = normalize(cameraPos - FragPos);

    float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess);
    vec3 specular = texture(material.specular, TexCoord).rgb * specularAmount * lightColor;

    vec3 diffuse = texture(material.diffuse, TexCoord).rbg * max(dot(lightDir, Normal), 0) * lightColor;

    //vec3  = material.diffuse * max(dot(lightDir, Normal) , 0)* lightColor;
    vec3 ambient =   texture(material.diffuse, TexCoord).rbg * material.ambient * ambientColor;
    
     FragColor = vec4((ambient + diffuse ) * objColor  , 1.0);
    
    //FragColor = vec4 (1.0f, 0.5f, 0.31f,1);   //coral
    //FragColor = mix(texture(ourTexture, TexCoord) , texture(ourFace, TexCoord), 0.5);
   // FragColor =vec4(diffuse, 0);

} 
