#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../render/render.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <Windows.h>
#include <string>

#define STB_IMAGE_IMPLEMENTATION

#include "../resources/stb_image.h"

float asa = 0.0;
float asax = 0.0;
float asay = 0.0;
float asaz = 0.0;



//std::vector

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);

glm::vec3 cameraPos = glm::vec3(7.0f, 10.0f, 11.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}


bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;


int main()
{
    srand(time(NULL));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    class Shader::Shader frs("../mat/shader004.vs", "../mat/shader004.fs", nullptr);
    class Shader::Shader frs2("../mat/shader004.vs", "../mat/shader004.fs", nullptr);
    
    glm::vec3 lightColor(0.0f, 0.0f, 1.0f);
    glm::vec3 objColor(0.0f, 0.0f, 1.0f);
    glm::vec3 result = lightColor * objColor;

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.1f, 0.1f, (float)result.x, (float)result.y , (float)result.z,
     0.5f, -0.5f, -0.5f,  0.4f, 0.1f, (float)result.x, (float)result.y , (float)result.z,
     0.5f,  0.5f, -0.5f,  0.4f, 0.4f, (float)result.x, (float)result.y , (float)result.z,
     0.5f,  0.5f, -0.5f,  0.4f, 0.4f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f,  0.5f, -0.5f,  0.1f, 0.4f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f, -0.5f, -0.5f,  0.1f, 0.1f, (float)result.x, (float)result.y , (float)result.z,
                                      
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f, -0.5f,  0.5f,  3.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f,  0.5f,  0.5f,  3.0f, 3.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f,  0.5f,  0.5f,  3.0f, 3.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f,  0.5f,  0.5f,  0.0f, 3.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
                                      
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
                                     
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
                                      
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
                                     
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, (float)result.x, (float)result.y , (float)result.z,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, (float)result.x, (float)result.y , (float)result.z
    };


    glm::vec3 head(0.0f, 0.0f, 1.0f);
    std::vector <glm::vec3> cells{
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 2.0f),
        glm::vec3(0.0f, 0.0f, 3.0f),
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // light
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1, texture2;
   
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("../texture/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //show to how to use png
    data = stbi_load("../texture/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    frs.use();
    frs.setInt("texture1", 0);
    frs.setInt("texture2", 1);

    unsigned int texture3, texture4;

    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //int width, height, nrChannels;
    data = stbi_load("../texture/wall.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //show to how to use png
    data = stbi_load("../texture/stone.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    frs2.setInt("texture3", 0);
    frs2.setInt("texture4", 1);

    // -----------
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view = glm::mat4(1.0f);
    //glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    auto ron = &head.z;
    float temp = 0;
    std::cout << *ron << " " << ron;
    float nor = 1;

    glm::vec3 appleCor(0.0f);
    glm::vec3 wallCor(0.0f);
    std::string Map[16] = {
        "###############",
        "#.............#",
        "#.............#",
        "#.............#",
        "#....######...#",
        "#.............#",
        "#.............#",
        "#.............#",
        "###############",
    };

    bool temp1 = false;
    while (!glfwWindowShouldClose(window))
    {
        
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // camera/view transformation
        glm::mat4 view = glm::mat4(1.0f); // 5make sure to initialize matrix to identity matrix first
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        frs.setMat4("view", view);

        frs.use();

        frs2.setMat4("view", view);


        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        frs.setMat4("projection", projection);

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            ron = &head.x;
            nor = 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            ron = &head.x;
            nor = -1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            ron = &head.z;
            nor = 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            ron = &head.z;
            nor = -1.0f;
        }

        temp += deltaTime;
        if (temp >= 0.3f)           // Speed
        {
            temp = 0;
            for (int i = 1; i < cells.size(); i++)
            {
                cells[cells.size() - i] = cells[cells.size() - i - 1];
            }
            cells[0] = head;
            *ron -= 1.0f * nor;
        }

        
        // render boxes
        
        glBindVertexArray(VAO);
        for (int i = 0; i != cells.size(); i++)
        {
            // Cells
            // calculate the model  matrix for each object and pass it to shader befor drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cells[i]);

            /*float angle = 20.0f * i;*/
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));

            frs.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // Head
            glm::mat4 model1 = glm::mat4(1.0f);
            model1 = glm::translate(model1, head);

            model1 = glm::rotate(model1, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));

            frs.setMat4("model", model1);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindTexture(GL_TEXTURE_2D, texture1);

            glm::mat4 apple = glm::mat4(1.0f);
            if (head == appleCor)
            {
                appleCor = glm::vec3((float)(rand() % 13 + 1), 0.0f, (float)(rand() % 7 + 1));
                int temp = cells.size();
                cells.push_back(glm::vec3(cells[temp - 1]));
            }
            apple = glm::translate(apple, appleCor);

            apple = glm::rotate(apple, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));
            apple = glm::scale(apple, glm::vec3(0.7f));
            frs.setMat4("model", apple);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glDrawArrays(GL_TRIANGLES, 0, 36); 
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0);

            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    if (Map[i][j] == '#')
                    {
                        glm::mat4 map1 = glm::mat4(1.0f);
                        map1 = glm::translate(map1, glm::vec3((float)j, 0.0f, (float)i));
                        map1 = glm::rotate(map1, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 1.0f));
                        map1 = glm::scale(map1, glm::vec3(1.0f, 0.5f, 1.0f));
                        frs.setMat4("model", map1);
                        glDrawArrays(GL_TRIANGLES, 0, 36);
                    }
                    else
                    {

                    }
                }
            }
            

        }

        glm::vec3 model2Cord (1.0f);
       
        frs2.use();

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, texture4);

        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(model2Cord.x + 0.01f, model2Cord.y, model2Cord.z));

        model2 = glm::rotate(model2, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));

        frs.setMat4("model", model2);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    // Fullscreen
    /*if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", glfwGetPrimaryMonitor(), NULL);
    }*/
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}