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

#include "graphics/LineBatch.h"

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

int attrs[] = { 2, 4, 0 };

float vertices[] = {
    //x        y   r   g   b   a
     0.0f,   0.01f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.0f,  -0.01f, 1.0f, 1.0f, 1.0f, 1.0f,

     0.01f,   0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.01f,   0.0f, 1.0f, 1.0f, 1.0f, 1.0f
};

int main()
{

    Window::initialize(WIDTH, HEIGHT, "Hi_player)");
    Events::initialize();
    Camera* camera = new Camera(vec3(12., 5.f, 10.), radians(90.0f));


    Shader first("../src/shaders/Shader_1.vs", "../src/shaders/Shader_1.fs");
    Shader lightCubeShader("../src/shaders/LightCubeShader_1.vs", "../src/shaders/LightCubeShader_1.fs");
    Shader for_lines("../src/shaders/ShV1.vs", "../src/shaders/ShV1.fs");
    Shader crosshair_shader("../res/main_crosshair_shader.vs", "../res/main_crosshair_shader.fs");
	Shader main_voxel_box_shader("../res/main_line_shader.vs", "../res/main_line_shader.fs");
    
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


    Shader chunkbox_shader("../res/main_line_shader.vs", "../res/main_line_shader.fs");
        
    Mesh crosshairMesh(vertices, 4, attrs);

    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };

    int attrs[] = { 3, 2, 3, 0 };
      

    Chunks* chunks = new Chunks(4, 4, 4);
    Mesh** chunksMesh = new Mesh * [chunks->volume];
    MarchingCubeRenderer renderer(5 * CHUNK_VOL, attrs);
    for (size_t i = 0; i < chunks->volume; i++) {
        chunksMesh[i] = renderer.render(chunks->chunks[i]);
    }


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float lastFrame = static_cast<float>(glfwGetTime());
    float deltaTime;

    float camX = 0.0f;
    float camY = 0.0f;

    glm::vec3 lightPos;

	LineBatch* voxel_box = new LineBatch(24);

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

        if (Events::jpressed(GLFW_KEY_G)) {
            for (int i = 0; i < chunks->volume; i++)
            {
                //chunks->chunks[i]->ChunkBoxDrawer();
                chunks->chunks[i]->shouldToDraw = !chunks->chunks[i]->shouldToDraw;
            }
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
            int texture_index;
            //ray cast
            {
                vec3 end;       //end vector
                vec3 norm;      //normal vector(for object which is wached)
                vec3 iend;                                                  //ray langh
                Marching_cubes* vox = chunks->rayCast(camera->position, camera->front, 10.0f, end, iend);
                if (vox != nullptr) {
                    voxel_box->box(iend.x + 0.5f, iend.y + 0.5f, iend.z + 0.5f, 1.005f, 1.005f, 1.005f, 0, 0, 0, 0.5f);

                    if (Events::jclicked(GLFW_MOUSE_BUTTON_1)) {
                        int x = (int)iend.x;
                        int y = (int)iend.y;
                        int z = (int)iend.z;
                        chunks->set(x, y, z, 0, 0);
                    }
                    if (Events::jclicked(GLFW_MOUSE_BUTTON_2)) {
                        int x = (int)(iend.x) + (int)(norm.x);
                        int y = (int)(iend.y) + (int)(norm.y);
                        int z = (int)(iend.z) + (int)(norm.z);
                        chunks->set(x, y, z, 1, texture_index);
                    }

                }
            }

            Chunk* closes[27];
            for (size_t i = 0; i < chunks->volume; i++)
            {
                Chunk* chunk = chunks->chunks[i];
                if (!chunk->modified) continue;
                chunk->modified = false;

                if (chunksMesh[i] != nullptr)
                    delete chunksMesh[i];

                for (int i = 0; i < 27; i++)
                {
                    closes[i] = nullptr;
                }
                for (int j = 0; j < chunks->volume; j++)
                {
                    Chunk* other = chunks->chunks[j];

                    int ox = other->xpos - chunks->chunks[i]->xpos;
                    int oy = other->ypos - chunks->chunks[i]->ypos;
                    int oz = other->zpos - chunks->chunks[i]->zpos;

                    if (abs(ox) > 1 || abs(oy) > 1 || abs(oz) > 1) continue;

                    ox += 1;
                    oy += 1;
                    oz += 1;
                    closes[(oy * 3 + oz) * 3 + ox] = other;
                }
                Mesh* mesh = renderer.render(chunk);
                chunksMesh[i] = mesh;
                
            }

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
                        Mesh* mesh = chunksMesh[i];

                        first.use();
                        model228 = mat4(1.0f);
                        model228 = glm::translate(model228, vec3(chunk->xpos * CHUNK_W, chunk->ypos * CHUNK_H, chunk->zpos * CHUNK_D));
                        first.setMat4("model", model228);
                        chunksMesh[i]->draw(GL_TRIANGLES);

                        chunkbox_shader.use();
                        chunkbox_shader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
                        chunkbox_shader.setMat4("view", view);
                        chunks->chunks[i]->ChunkBoxDrawer(chunkbox_shader);
						
						main_voxel_box_shader.use();
                        main_voxel_box_shader.setMat4("projection", camera->getProjection());
                        main_voxel_box_shader.setMat4("view", camera->getView());
                        main_voxel_box_shader.setMat4("model", glm::mat4(1.f));
                        voxel_box->render();
                    }

                    crosshair_shader.use();
                    crosshairMesh.draw(GL_LINES);
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





