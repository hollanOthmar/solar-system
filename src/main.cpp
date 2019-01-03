#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include "CGALHandler.h"
#include "renderUtility.h"
#include "camera.hpp"
#include "controls.h"
#include "Renderer.h"
#include "Planet.h"
#include "shader.hpp"
#include "Sun.h"

//SETTINGS
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;
GLFWwindow *window;

Camera camera;
double lastFrame;
double deltaTime;

std::vector<Vertex> sphereData;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);


void update();

bool initWindow();
bool initGL();

int main()
{
    if (!initWindow())
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    } else {

        if(!initGL())
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        //generate sphere mesh
        generateSphereMesh(sphereData);

        //lightstuff
        glm::vec3 lightColor = glm::vec3(1.0,1.0,1.0);
        glm::vec3 lightPos = glm::vec3(0.0,0.0,0.0);
        Shader lightShader("../shaders/light.vs","../shaders/light.fs");
        Sun sun(0.5,lightColor,lightPos);
        sun.init();

        Renderer lightRenderer(sphereData);
        lightRenderer.init();

        //planets stuff!
        double orbits[] = {-12.0,-9.0,-6.0,-3.0};

        //1. Create renderers of any object you want to render
            //i.e. Renderer render(data);
            //render.init()
        Renderer renderer(sphereData);
        renderer.init();

        //2. Create the planets!!
            //forEach, Planet planet(scale,*render)
        Shader planetsShader("../shaders/object.vs","../shaders/object.fs");
        std::vector<Planet> planets;
        float scale = 0.3f;
        for (int i = 0; i < 4; i++)
        {
            planets.push_back(Planet(scale,lightColor,lightPos,orbits[i]));
        }
        for(auto& planet : planets)
        {
            planet.init();
        }

        //init time frames
        lastFrame = 0.0f;
        deltaTime = 0.0f;
        while(!glfwWindowShouldClose(window))
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            processInput(window,camera,deltaTime);

//             glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //update camera after processing window events!
            update();
            glm::mat4 view = glm::mat4(1.0);
            glm::mat4 projection = glm::mat4(1.0);
            glm::vec3 campos = camera.getPos();
            view = camera.getView();
            projection = camera.getProjection();


            //Render stuff!
            //forEach: planet.update()
            //          renderer.render()
            for(auto& planet : planets)
            {
                planet.draw(view,projection,campos,planetsShader);
                renderer.render();
                planet.update(deltaTime);
            }

            //render lightsource!
//            lightRenderer.bindVAO(lightRenderer.getVAO());
            sun.draw(view,projection,campos,lightShader);
            lightRenderer.render();


            //checking errors
            GLenum err;
            while ((err = glGetError()) != GL_NO_ERROR) {
                std::cerr << "OpenGL error: " << err << std::endl;
            }


            glfwSwapBuffers(window);
            glfwPollEvents();
        }
//        glDeleteVertexArrays(1, &sphereVAO);
//        glDeleteBuffers(1, &sphereVBO);
        glfwTerminate();
    }


    return 0;
}

bool initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //creating window object
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Solar System",NULL, NULL);
    if (window == nullptr)
    {
        return false;
    }

    glfwMakeContextCurrent(window);

    //Registering callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

     //tell GLFW to capture our mouse
     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;

}

bool initGL()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return false;
    }

    //NOTE! For OSX, framebuffer size should be set twice as much as window size!
    glViewport(0,0,SCR_WIDTH*2,SCR_HEIGHT*2);
    //configure global opengl state
    glEnable(GL_DEPTH_TEST);
    //setting polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return true;
}

void update()
{
    camera.update();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.updateCameraDirection(xpos,ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.zoom(yoffset);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}