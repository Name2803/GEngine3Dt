#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <cmath>



#include "graphics/ShaderCl.h"
#include "window/window.h"
#include "window/Events.h"
#include "window/Camera.h"
#include "graphics/Texture.h"

// settings
const unsigned int WIDTH = 1200;
const unsigned int HEIGHT = 720;



int main()
{

    Window::initialize(WIDTH, HEIGHT, "Hi_player)");
    Events::initialize();
    Camera* camera = new Camera(vec3(0., 5.f, 0.), radians(90.0f));

    Shader first("../src/shaders/Shader_1.vs", "../src/shaders/Shader_1.fs");
    Shader lightCubeShader("../src/shaders/LightCubeShader_1.vs", "../src/shaders/LightCubeShader_1.fs");
    
    
    first.use();
    Texture diffuseMap("../data/picturs/container_diffuse.png");
    Texture specularMap("../data/picturs/lighting_maps_specular_color.png");
    Texture emissionMap("../data/picturs/matrix.jpg");
    first.setInt("material.diffuse", 0);
    first.setInt("material.specular", 1);
    first.setInt("material.emission", 2);
    glUseProgram(NULL);

    lightCubeShader.use();
    Texture lightCubeTexture("../data/picturs/lightCube.jpg");
    lightCubeShader.setInt("texture1", 0);
    glUseProgram(NULL);




    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
                                                            
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
                                                            
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
                                                            
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
                                                            
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
                                                            
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f
    };
    // world space positions of our cubes
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
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // texture coords)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normals
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);
    


    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // texture coords)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glEnable(GL_DEPTH_TEST);


    float lastFrame = static_cast<float>(glfwGetTime());
    float deltaTime;

    float camX = 0.0f;
    float camY = 0.0f;

    glm::vec3 lightPos = glm::vec3(1.0f);

    while (!Window::isShouldClose()) 
    {
        int speed = 3;

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.1f, 0.1f, 1);

        if (Events::jpressed(GLFW_KEY_ESCAPE)) {
            Window::setShouldClose(true);
        }
        if (Events::clicked(GLFW_MOUSE_BUTTON_1)) {
            glClearColor(0.8f, 0.4f, 0.2f, 1);
        }

        if (Events::pressed(GLFW_KEY_W)) {
            camera->position += speed * deltaTime * camera->front;
        }

        if (Events::pressed(GLFW_KEY_S)) {
            camera->position -= speed * deltaTime * camera->front;
        }

        if (Events::pressed(GLFW_KEY_A)) {
            camera->position -= speed * deltaTime * camera->right;
        }
        if (Events::pressed(GLFW_KEY_D)) {
            camera->position += speed * deltaTime * camera->right;
        }

        if (Events::pressed(GLFW_KEY_SPACE)) {
            camera->position.y += speed * deltaTime * camera->up.y;
        }

        if (Events::pressed(GLFW_KEY_LEFT_SHIFT)) {
            camera->position.y -= speed * deltaTime * camera->up.y;
        }

        if (Events::jpressed(GLFW_KEY_TAB)) {
            Events::toogleCursor();
        }

        camera->rotate(-Events::deltaY / Window::width, -Events::deltaX / Window::height, 0);

        if (Events::_cursor_locked) {
            camY += -Events::deltaY / Window::height * 2;
            camX += -Events::deltaX / Window::height * 2;

            if (camY < -radians(89.0f)) {
                camY = -radians(89.0f);
            }
            if (camY > radians(89.0f)) {
                camY = radians(89.0f);
            }

            camera->rotation = mat4(1.0f);
            camera->rotate(camY, camX, 0);
                    
        }

        
            first.use();
            first.setVec3("viewPos", camera->position);
            

            // create transformations
            glm::mat4 view = camera->getView(); // make sure to initialize matrix to identity matrix first
            glm::mat4 projection = camera->getProjection();

            // pass transformation matrices to the shader
            first.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            first.setMat4("view", view);
            // render boxe
            
            first.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
            first.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
            first.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
            first.setVec3("light.position", lightPos);

            first.setFloat("time", glfwGetTime());

            // material properties
            first.setFloat("material.shininess", 64.0f);
            glBindVertexArray(VAO);
            {
                // calculate the model matrix for each object and pass it to shader before drawing

                glm::mat4 model = glm::mat4(1.0f);
                float angle = 20.0f*glfwGetTime();
                //model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.3f, 0.0f));
                model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
               // model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
                first.setMat4("model", model);

                // bind diffuse map
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, diffuseMap.id);
                // bind specular map
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, specularMap.id);
                // bind emission map
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, emissionMap.id);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }


        

            // set light position
            lightCubeShader.use();
            float lightX = 2.0f * sin(glfwGetTime());
            float lightY = -0.3f;
            float lightZ = 1.5f * cos(glfwGetTime());
            lightPos = glm::vec3(lightX, lightY, lightZ);

            // pass transformation matrices to the shader
            lightCubeShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            lightCubeShader.setMat4("view", view);
            glm::mat4 model_1 = glm::mat4(1.0f);
            model_1 = glm::translate(model_1, lightPos);
            model_1 = glm::scale(model_1, glm::vec3(0.1f, 0.1f, 0.1f));
            lightCubeShader.setMat4("model", model_1);

            // bind diffuse map
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, lightCubeTexture.id);

            glBindVertexArray(lightCubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        

        Window::swapBuffers();
        Events::pullEvents();
    }
    Window::terminate();
	return 0;
}