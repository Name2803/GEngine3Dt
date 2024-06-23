#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <cmath>


#include <Windows.h>

#include "graphics/ShaderCl.h"
#include "window/window.h"
#include "window/Events.h"
#include "window/Camera.h"
#include "graphics/Texture.h"
#include "mesh/Mesh.h"
#include "marching_cubes/marching_cubes.h"
#include "marching_cubes/chunk.h"
#include "marching_cubes/chunks.h"
#include "graphics/marching_cube_renderer.h"

// all extra functions 

#include "helper_function/helper_function.h"

// settings
const unsigned int WIDTH = 1200;
const unsigned int HEIGHT = 720;

#define CH_HEIGHT 8     //z -> y(because of cameara derecion z = -y axie)
#define CH_WIDTH 1      //y -> z
#define CH_WIDE 32      //x -> x

int amount;
int** chankmass;


struct Verices {
    float* vertices = nullptr;
    int amount = 0;
};


int main()
{

    Window::initialize(WIDTH, HEIGHT, "Hi_player)");
    Events::initialize();
    Camera* camera = new Camera(vec3(0., 5.f, 0.), radians(90.0f));


    Shader first("../src/shaders/Shader_1.vs", "../src/shaders/Shader_1.fs");
    Shader lightCubeShader("../src/shaders/LightCubeShader_1.vs", "../src/shaders/LightCubeShader_1.fs");
    Shader for_lines("../src/shaders/ShV1.vs", "../src/shaders/ShV1.fs");
    
    first.use();
    Texture diffuseMap("../data/picturs/container_diffuse.png");
    Texture specularMap("../data/picturs/lighting_maps_specular_color.png");
    Texture emissionMap("../data/picturs/matrix.jpg");
    Texture spotlightLightMap("../data/picturs/batman_spotlight.jpg");
    first.setInt("material.diffuse", 0);
    first.setInt("material.specular", 1);
    first.setInt("material.emission", 2);
    first.setInt("material.spotlight", 3);
    glUseProgram(NULL);

    lightCubeShader.use();
    Texture lightCubeTexture("../data/picturs/lightCube.jpg");
    lightCubeShader.setInt("texture1", 0);
    glUseProgram(NULL);

        
    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };

    int attrs[] = { 3, 2, 3, 0 };
      

    Chunks* chunks = new Chunks(4, 1, 4);
    Mesh** meshes = new Mesh * [chunks->volume];
    MarchingCubeRenderer renderer(5 * CHUNK_VOL, attrs);
    for (size_t i = 0; i < chunks->volume; i++) {
        meshes[i] = renderer.render(chunks->chunks[i]);
    }


    glEnable(GL_DEPTH_TEST);


    float lastFrame = static_cast<float>(glfwGetTime());
    float deltaTime;

    float camX = 0.0f;
    float camY = 0.0f;

    glm::vec3 lightPos;

    while (!Window::isShouldClose()) 
    {
        int speed = 3;

        glm::mat4 extra = glm::mat4(1.0f);

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.5f, 0.6f, 0.6f, 1);

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



            if (Events::pressed(GLFW_KEY_E)) {
                extra = glm::rotate(extra, glm::radians(-20.f), glm::vec3(0.5f, 0.0f, -3.0f));
            }
            else {
                extra = glm::rotate(extra, glm::radians(0.f), glm::vec3(0.5f, 0.0f, -3.0f));
            }
            first.setMat4("extra", extra);




            first.use();

            // directional light
            first.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
            first.setVec3("dirLight.ambient", 0.5f, 0.5f, 0.5f);
            first.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
            first.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
            // point light 1
            first.setVec3("pointLights[0].position", pointLightPositions[0]);
            first.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
            first.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
            first.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
            first.setFloat("pointLights[0].constant", 1.0f);
            first.setFloat("pointLights[0].linear", 0.09f);
            first.setFloat("pointLights[0].quadratic", 0.032f);
            // point light 2
            first.setVec3("pointLights[1].position", pointLightPositions[1]);
            first.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
            first.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
            first.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
            first.setFloat("pointLights[1].constant", 1.0f);
            first.setFloat("pointLights[1].linear", 0.09f);
            first.setFloat("pointLights[1].quadratic", 0.032f);
            // point light 3
            first.setVec3("pointLights[2].position", pointLightPositions[2]);
            first.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
            first.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
            first.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
            first.setFloat("pointLights[2].constant", 1.0f);
            first.setFloat("pointLights[2].linear", 0.09f);
            first.setFloat("pointLights[2].quadratic", 0.032f);
            // point light 4
            first.setVec3("pointLights[3].position", pointLightPositions[3]);
            first.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
            first.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
            first.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
            first.setFloat("pointLights[3].constant", 1.0f);
            first.setFloat("pointLights[3].linear", 0.09f);
            first.setFloat("pointLights[3].quadratic", 0.032f);
            // spotLight
            first.setVec3("spotLight.position", camera->position);
            first.setVec3("spotLight.direction", camera->front);
            first.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            first.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            first.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
            first.setFloat("spotLight.constant", 1.0f);
            first.setFloat("spotLight.linear", 0.09f);
            first.setFloat("spotLight.quadratic", 0.032f);
            first.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            first.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

            first.use();
            first.setVec3("viewPos", camera->position);


            // create transformations
            glm::mat4 view = camera->getView(); // make sure to initialize matrix to identity matrix first
            glm::mat4 projection = camera->getProjection();

            // pass transformation matrices to the shader
            // render boxe
            for_lines.use();
            for_lines.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            for_lines.setMat4("view", view);

            first.use();
            first.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            first.setMat4("view", view);

            first.setFloat("time", glfwGetTime());

            // material properties
            first.setFloat("material.shininess", 64.0f);

            // for (unsigned int i = 0; i < amount; i++)
            {
                if (1) {
                    // calculate the model matrix for each object and pass it to shader before drawing
                    // bind diffuse map
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, diffuseMap.id);
                    // bind specular map
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, specularMap.id);
                    // bind emission map
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, emissionMap.id);
                    // bind spotlightLight map
                    glActiveTexture(GL_TEXTURE3);
                    glBindTexture(GL_TEXTURE_2D, spotlightLightMap.id);
                    glm::mat4 model228 = glm::mat4(1.0f);


                    for (int i = 0; i < chunks->volume; i++) {
                        Chunk* chunk = chunks->chunks[i];
                        Mesh* mesh = meshes[i];

                        first.use();
                        model228 = mat4(1.0f);
                        model228 = glm::translate(model228, vec3(chunk->x * CHUNK_W, chunk->y * CHUNK_H, chunk->z * CHUNK_D));
                        first.setMat4("model", model228);
                        meshes[i]->draw(GL_TRIANGLES);
                    }


                }
            }
        }
        Window::swapBuffers();
        Events::pullEvents();
    }

    delete chunks;
    Window::terminate();
	return 0;
}





