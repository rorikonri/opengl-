//about テクスチャ will in 142行(Init Material).
//about オブジェクトコントロール will in 196行.

#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include"Shader.h"
#include"material.h"

#include "stb_image.h"
#include<stdio.h>
#include<iostream>
#include"Camera.h"
#include"LightDirectional.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot);
        #pragma region Model Data
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
#pragma endregion
        #pragma region cubePositions
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion
        #pragma region texCoords
float texCoords[] = {
    0.0f, 0.0f, // 左下角
    1.0f, 0.0f, // 右下角
    0.5f, 1.0f // 上中
};
#pragma endregion

#pragma region Camera Declare
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion  

#pragma region Light Declare
LightDirectional light = LightDirectional(glm::vec3 (10.0f, 10.0f, -5.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0));
#pragma endregion  

    int main()
    {
        int width = 800;
        int height = 600;
        glm::mat4 modelMat;
        glm::mat4 projMat;
        projMat = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 viewMat;
        #pragma region Open_Glfw_Windows
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            printf("Failed to create GLFW window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);


        //Init GLEW
        glewExperimental = true;
        if(glewInit()!= GLEW_OK)
        { 
            printf("init GLEW failed");
            glfwTerminate();
            return -1;
        }
        
        glViewport(0, 0, 800, 600);
        glEnable(GL_DEPTH_TEST);
    #pragma endregion
        #pragma region Init Shader Program
        Shader* testShader = new Shader("vertexSource.vert", "fragmentSource.frag");
#pragma endregion
        #pragma region Init Material
        Material* myMaterial = new Material(testShader,
            LoadImageToGPU("container2.jpg", GL_RGB, GL_RGB, Shader::DIFFUSE),    //ambient  テクスチャの設定
            LoadImageToGPU("container2_specular.jpg", GL_RGB, GL_RGB, Shader::SPECULAR),
            glm::vec3(1.0f, 1.0f, 1.0f),    //diffuse
                                //specular
            32.0f);                         //shininess
        #pragma endregion


        #pragma region Init and Load Models to VAO,VBO
        //VAOの初期化
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        //VBOの初期化
        unsigned int VBO;
        glGenBuffers(1,&VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
         
        

        //頂点座標
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //法線ベクトル
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //uv座標
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

#pragma endregion
        
       // unsigned int TexBufferA;
       // TexBufferA = LoadImageToGPU("zhuankuai.jpg",GL_RGB, GL_RGB, 0);
        testShader->use();
       // glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture"), 0);

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            viewMat = camera.GetViewMatrix();
            for (unsigned int i = 0; i < 1; i++)
            {
                Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));

                glm::mat4 modelMat;
                modelMat = glm::translate(modelMat, cubePositions[i]);

                //コントロール
                //modelMat = glm::rotate(modelMat, ((float)glfwGetTime() *2) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));    //光源回転
                //viewMat = glm::rotate(viewMat, ((float)glfwGetTime() ) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));    //オブジェクト回転
                //viewMat = glm::translate(viewMat,  glm::vec3(((float)glfwGetTime() * 1), 1.0f, 0.0f));    //オブジェクト移動

                glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
                glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
                glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
                glUniform3f(glGetUniformLocation(testShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
                glUniform3f(glGetUniformLocation(testShader->ID, "ambientColor"), 0.5f, 0.5f, 0.5f);
                glUniform3f(glGetUniformLocation(testShader->ID, "lightPos"), light.position.x, light.position.y, light.position.z);
               // glUniform3f(glGetUniformLocation(testShader->ID, "lightColor"), light.color.x, light.color.y, light.color.y);
                glUniform3f(glGetUniformLocation(testShader->ID, "lightColor"), 1.0f, 1.0f, 1.0f);
                glUniform3f(glGetUniformLocation(testShader->ID, "lightDir"), light.direction.x, light.direction.y, light.direction.z);
                glUniform3f(glGetUniformLocation(testShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
 
                myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
                //myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
                myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
                myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
               // myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
                myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
                 
                

                glDrawArrays(GL_TRIANGLES, 0, 36);
                
            }

            glfwPollEvents();
            glfwSwapBuffers(window);
            camera.UpdataCameraPos();
            
        }   
        return 0;
    }
#pragma region LoadImageToGPU
    unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot){
        //テクスチャバッファの設定
        unsigned int TexBuffer;
       glGenTextures(1, &TexBuffer);
       glActiveTexture(GL_TEXTURE0 + textureSlot);
       glBindTexture(GL_TEXTURE_2D, TexBuffer);

        int width, height, nrChannels;
        width = 800;
        height = 600;
        unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            printf("load image failed");
        }
        stbi_set_flip_vertically_on_load(true);
        stbi_image_free(data);
        return TexBuffer;
    }
#pragma endregion

#pragma region Input Declare
    float lastX;
    float lastY;
    bool firstMouse = true;

    void processInput(GLFWwindow* window){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.speedZ = 1.0f;
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.speedZ = -1.0f;
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.speedX = -1.0f;
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.speedX = 1.0f;
        else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            camera.speedY = -1.0f;
        else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            camera.speedY = 1.0f;
        else
            camera.speedZ = camera.speedX = camera.speedY =0;
    }


    void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
        float deltaX, deltaY;
        
        if (firstMouse == true)
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }
        deltaX = xPos - lastX;
        deltaY = yPos - lastY;
        lastX = xPos;
        lastY = yPos;

        camera.ProcessMouseMovement(deltaX, deltaY);
        //printf("%f\n", xPos);
    }
 #pragma endregion