// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 1080, HEIGHT = 720;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animaCompleja();

// Camera
Camera camera(glm::vec3(30.0f, 10.0f, 50.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


// Light attributes
glm::vec3 lightPos(0.5f, 0.5f, 2.5f);
float movelightPos = 0.0f;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;

//Variables para animaciones
float columpiar = 0;
float girar = 0;
float tiempo;
float movKitX = 0.0;
float movKitZ = 0.0;
float rotKit = 0.0;
float movKitX2 = 0.0;
float movKitZ2 = 0.0;
float movKitZ3 = 0.0;
float movKitX3 = 0.0;
float movKitX4 = 0.0;
float movKitZ4 = 0.0;
float movKitZ5 = 0.0;
float movKitX5 = 0.0;
float rotarCil = 0.0;

bool girarCil = false;
bool movAdel = false; 
bool giroRueda;
bool columadel;
bool activanim = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;
bool recorrido6 = false;
bool recorrido7 = false;
bool recorrido8 = false;
bool recorrido9 = false;

int cil = 0;

glm::vec3 PosIniAuto1(-180.0f, 0.0f, -50.0f);
glm::vec3 PosIniRueda1Auto1(-177.6f, 1.4f, -53.7f);
glm::vec3 PosIniRueda2Auto1(-182.35f, 1.4f, -53.7f);
glm::vec3 PosIniRueda3Auto1(-177.6f, 1.4f, -46.5f);
glm::vec3 PosIniRueda4Auto1(-182.35f, 1.4f, -46.5f);
//
//glm::vec3 PosIniAuto2(-180.0f, 0.0f, -50.0f);
//glm::vec3 PosIniRueda1Auto2(-177.6f, 1.4f, -53.7f);
//glm::vec3 PosIniRueda1Auto2(-177.6f, 1.4f, -53.7f);
//glm::vec3 PosIniRueda1Auto2(-177.6f, 1.4f, -53.7f);
//glm::vec3 PosIniRueda1Auto2(-177.6f, 1.4f, -53.7f);
//
glm::vec3 PosIniAuto3(135.0f, 0.0f, 50.0f);
glm::vec3 PosIniRueda2Auto3(132.6f, 1.4f, 46.4f); 
glm::vec3 PosIniRueda1Auto3(137.35f, 1.4f, 46.4f);
glm::vec3 PosIniRueda4Auto3(132.6f, 1.4f, 53.6f);
glm::vec3 PosIniRueda3Auto3(137.35f, 1.4f, 53.6f);

glm::vec3 PosIniAuto4(-135.0f, 0.0f, 50.0f);
glm::vec3 PosIniRueda1Auto4(-137.35f, 1.4f, 53.6f);
glm::vec3 PosIniRueda2Auto4(-132.6f, 1.4f, 53.6f);
glm::vec3 PosIniRueda3Auto4(-137.35f, 1.4f, 46.4f);
glm::vec3 PosIniRueda4Auto4(-132.6f, 1.4f, 46.4f);

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");
    Shader lampshader("Shaders/lamp.vs", "Shaders/lamp.frag");
    Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
    Shader Anim("Shaders/anim.vs", "Shaders/anim.frag");


    // Load models
    Model agua((char*)"Models/skybox/agua.obj");
    

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,


        // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    GLuint indices[] =
    {  // Note that we start from 0!
        36,37,38,
        37,38,39

    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // Load textures
    Model skybox((char*)"Models/skybox/skybox2.obj");
    Model botamon((char*)"Models/Botamon/botamon.obj");
    Model suelo((char*)"Models/Piso/pasto1.obj");
    Model arbol((char*)"Models/arbol/arbol.obj");
    Model pabumon((char*)"Models/Pabumon/pabumon.obj");
    Model huevo1((char*)"Models/Digihuevos/huevo1.obj");
    Model huevo2((char*)"Models/Digihuevos/huevo2.obj");
    Model cubo((char*)"Models/Cubos/cubo.obj");
    Model cilindro1((char*)"Models/Cubos/cilindro1.obj");
    Model cilindro2((char*)"Models/Cubos/cilindro2.obj");
    Model cilindro3((char*)"Models/Cubos/cilindro3.obj");
    Model cilindro4((char*)"Models/Cubos/cilindro4.obj");
    Model cono1((char*)"Models/Cubos/cono1.obj");
    Model cono2((char*)"Models/Cubos/cono2.obj");
    Model cono3((char*)"Models/Cubos/cono3.obj");
    Model carro1((char*)"Models/Car/carro1.obj");
    Model carro2((char*)"Models/Car/carro2.obj");
    Model carro3((char*)"Models/Car/carro3.obj");
    Model carro4((char*)"Models/Car/carro4.obj");
    Model rueda1((char*)"Models/Car/ruedaDelIzq.obj");
    Model rueda2((char*)"Models/Car/ruedaDelDer.obj");
    Model rueda3((char*)"Models/Car/ruedaTrasIzq.obj");
    Model rueda4((char*)"Models/Car/ruedaTrasDer.obj");
    Model puente((char*)"Models/Puente/puente.obj");
    Model columpio((char*)"Models/Columpio/estructura_columpio.obj");
    Model asientoColDer((char*)"Models/Columpio/columpio_der.obj");
    Model asientoColIzq((char*)"Models/Columpio/columpio_izq.obj");

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();
        animaCompleja();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.Use();
        GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(lightPosLoc, lightPos.x + movelightPos, lightPos.y + movelightPos, lightPos.z + movelightPos);
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        //// Set lights properties
        //glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.4f, 0.4f, 0.4f);
        //glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.5f, 0.5f, 0.5f);
        //glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);

        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 1.0f, 1.0f, 1.0f);

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        //Botamon
        // Set material properties
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.5f, 0.5f, 0.5f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 20.0f);

        // Draw the loaded model
        //Cuerpos de botamon

        //Botamon 1
        glm::mat4 model(1);



        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        model = glm::mat4(1);
        
        glBindVertexArray(0);

        //animación del agua
        Anim.Use();
        tiempo = glfwGetTime();
        modelLoc = glGetUniformLocation(Anim.Program, "model");
        viewLoc = glGetUniformLocation(Anim.Program, "view");
        projLoc = glGetUniformLocation(Anim.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 1.0f, 16.0f));
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        agua.Draw(Anim);

        glBindVertexArray(0);

        shader.Use();


        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        
        //Skybox
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
        model = glm::translate(model, glm::vec3(0.0f, 9.5f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        skybox.Draw(shader);
     
        //Botamon 
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
        model = glm::translate(model, glm::vec3(-100.0f, 0.0f, 250.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        botamon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
        model = glm::translate(model, glm::vec3(0.0f, 32.0f, 0.0f));
        model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        botamon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
        model = glm::translate(model, glm::vec3(-150.0f, 0.0f, 15.0f));
        model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        botamon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
        model = glm::translate(model, glm::vec3(-400.0f, 0.0f, 100.0f));
        model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        botamon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
        model = glm::translate(model, glm::vec3(-150.0f, 0.0f, -150.0f));
        model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        botamon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
        model = glm::translate(model, glm::vec3(200.0f, 0.0f, 150.0f));
        model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        botamon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
        model = glm::translate(model, glm::vec3(400.0f, 0.0f, -250.0f));
        model = glm::rotate(model, glm::radians(280.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        botamon.Draw(shader);


        //Pabumon
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.20f, 0.20f, 0.20f));
        model = glm::translate(model, glm::vec3(-300.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        pabumon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.20f, 0.20f, 0.20f));
        model = glm::translate(model, glm::vec3(-200.0f, 0.0f, -50.0f));
        model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        pabumon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.20f, 0.20f, 0.20f));
        model = glm::translate(model, glm::vec3(150.0f, 0.0f, -50.0f));
        model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        pabumon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.20f, 0.20f, 0.20f));
        model = glm::translate(model, glm::vec3(250.0f, 0.0f, 50.0f));
        model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        pabumon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.20f, 0.20f, 0.20f));
        model = glm::translate(model, glm::vec3(250.0f, 0.0f, -150.0f));
        model = glm::rotate(model, glm::radians(170.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        pabumon.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.20f, 0.20f, 0.20f));
        model = glm::translate(model, glm::vec3(400.0f, 0.0f, 250.0f));
        model = glm::rotate(model, glm::radians(240.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        pabumon.Draw(shader);

        //Digihuevo tipo 1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(100.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        huevo1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(60.0f, 0.0f, -20.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        huevo1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 10.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        huevo1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(100.0f, 0.0f, 30.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        huevo1.Draw(shader);

        //Digihuevo tipo 2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(50.0f, 0.0f, 35.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        huevo2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-100.0f, 0.0f, -40.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        huevo2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 20.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        huevo2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(50.0f, 0.0f, 90.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        huevo2.Draw(shader);

        //Dibujando arboles
        //Lado derecho

        //Cuadrante superior
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(5.0f, 0.0f, 15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(7.0f, 0.0f, 15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(9.0f, 0.0f, 15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(11.0f, 0.0f, 15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, 15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, 15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(5.0f, 0.0f, -15.0f));
        model = glm::rotate(model, glm::radians(160.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(7.0f, 0.0f, -15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(9.0f, 0.0f, -15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(11.0f, 0.0f, -15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, -15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, -15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, -13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, -11.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, -9.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, -7.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, -13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(11.0f, 0.0f, -13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(9.0f, 0.0f, -13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(11.0f, 0.0f, -11.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, -11.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, -9.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);
        
        //Cuadrante inferior

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(7.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(7.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(9.0f, 0.0f, 11.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(9.0f, 0.0f, 11.0f));
        model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(11.0f, 0.0f, 9.0f));
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(11.0f, 0.0f, 9.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, 7.0f));
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, 7.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);
        
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, 5.0f));
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, 5.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, 7.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, 9.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, 11.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(15.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, 7.0f));
        model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, 11.0f));
        model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(13.0f, 0.0f, 9.0f));
        model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(11.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(120.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(11.0f, 0.0f, 11.0f));
        model = glm::rotate(model, glm::radians(120.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(9.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(120.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        //Lado izquierdo
        //Cuadrante inferior
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 15.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-5.0f, 0.0f, -15.0f));
        model = glm::rotate(model, glm::radians(160.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-7.0f, 0.0f, -13.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-9.0f, 0.0f, 11.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, 11.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, 9.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, 7.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, 15.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-13.0f, 0.0f, 15.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-13.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-13.0f, 0.0f, 11.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-13.0f, 0.0f, 9.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-11.0f, 0.0f, 15.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-11.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-11.0f, 0.0f, 11.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-9.0f, 0.0f, 15.0f));
        model = glm::rotate(model, glm::radians(140.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-9.0f, 0.0f, 13.0f));
        model = glm::rotate(model, glm::radians(140.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-9.0f, 0.0f, 11.0f));
        model = glm::rotate(model, glm::radians(140.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 15.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        //Cuadrante superior
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-9.0f, 0.0f, -11.0f));
        model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-11.0f, 0.0f, 9.0f));
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-11.0f, 0.0f, -9.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-13.0f, 0.0f, 7.0f));
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-13.0f, 0.0f, -7.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, 5.0f));
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, -5.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, -7.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, -9.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, -11.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, -13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 0.0f, -15.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-13.0f, 0.0f, -15.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-13.0f, 0.0f, -13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-13.0f, 0.0f, -11.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-13.0f, 0.0f, -9.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-11.0f, 0.0f, -15.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-11.0f, 0.0f, -13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-11.0f, 0.0f, -11.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);


        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-9.0f, 0.0f, -15.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-9.0f, 0.0f, -13.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(-7.0f, 0.0f, -15.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        arbol.Draw(shader);

        //Figuras geometricas
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
        model = glm::translate(model, glm::vec3(12.0f, 1.0f, 10.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cubo.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
        model = glm::translate(model, glm::vec3(12.0f, 3.0f, 10.0f));
        model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cubo.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 3.0f));
        model = glm::translate(model, glm::vec3(18.0f, 7.8f, 20.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cilindro3.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
        model = glm::translate(model, glm::vec3(-10.0f, 1.0f, -10.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cubo.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
        model = glm::translate(model, glm::vec3(-10.0f, 3.0f, -10.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cubo.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 3.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 7.8f, -20.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cilindro1.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
        model = glm::translate(model, glm::vec3(9.2f, 1.0f, -11.8f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cubo.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
        model = glm::translate(model, glm::vec3(10.7f, 1.0f, -10.2f));
        model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cubo.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
        model = glm::translate(model, glm::vec3(12.2f, 1.0f, -8.7f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cubo.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
        model = glm::translate(model, glm::vec3(9.95f, 3.0f, -11.0f));
        model = glm::rotate(model, glm::radians(225.0f), glm::vec3(0.0f, -1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cubo.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
        model = glm::translate(model, glm::vec3(11.45f, 3.0f, -9.45f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cubo.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
        model = glm::translate(model, glm::vec3(10.7f, 5.0f, -10.225f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cubo.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        model = glm::translate(model, glm::vec3(32.2f, 21.5f, -30.225f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cono1.Draw(shader);


        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 3.0f));
        model = glm::translate(model, glm::vec3(15.7f, 1.5f, -16.0f));
        model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::rotate(model, glm::radians(60.0f), glm::vec3(-1.0f, 0.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cilindro2.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 3.5f, 26.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cono2.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        model = glm::translate(model, glm::vec3(-15.0f, 3.5f, 15.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cono3.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        model = glm::translate(model, glm::vec3(-20.0f, 1.0f, 9.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cilindro4.Draw(shader);

        //Carro1
        model = glm::mat4(1);
        model = glm::translate(model,PosIniAuto1 + glm::vec3(movKitX, 0, movKitZ));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        carro1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, PosIniRueda1Auto1+ glm::vec3(movKitX2, 0, movKitZ2));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model,PosIniRueda2Auto1 + glm::vec3(movKitX3, 0, movKitZ3));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model,PosIniRueda3Auto1 + glm::vec3(movKitX4, 0, movKitZ4));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda4.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model,PosIniRueda4Auto1 + glm::vec3(movKitX5, 0, movKitZ5));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda3.Draw(shader);

        //Carro2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(160.0f, 0.0f, -50.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        carro2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(162.35f, 1.4f, -53.7f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(157.6f, 1.4f, -53.7f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(162.35f, 1.4f, -46.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda3.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(157.6f, 1.4f, -46.5f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda4.Draw(shader);

        //Carro3
        model = glm::mat4(1);
        model = glm::translate(model, PosIniAuto3 + glm::vec3(movKitX, 0, movKitZ));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        carro3.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, PosIniRueda1Auto3 + glm::vec3(movKitX2, 0, movKitZ2));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, PosIniRueda2Auto3 + glm::vec3(movKitX3, 0, movKitZ3));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, PosIniRueda3Auto3 + glm::vec3(movKitX4, 0, movKitZ4));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda4.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, PosIniRueda4Auto3 + glm::vec3(movKitX5, 0, movKitZ5));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda3.Draw(shader);

        //Carro4
        model = glm::mat4(1);
        model = glm::translate(model, PosIniAuto4 + glm::vec3(-movKitX, 0, -movKitZ));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        carro4.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, PosIniRueda1Auto4 + glm::vec3(-movKitX2, 0, -movKitZ2));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, PosIniRueda2Auto4 + glm::vec3(-movKitX3, 0, -movKitZ3));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, PosIniRueda3Auto4 + glm::vec3(-movKitX4, 0, -movKitZ4));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda3.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, PosIniRueda4Auto4 + glm::vec3(-movKitX5, 0, -movKitZ5));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(girar), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        rueda4.Draw(shader);

        //Puente
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        puente.Draw(shader);

        //Columpio
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-120.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        columpio.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-121.0f, 18.0f, -6.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        model = glm::rotate(model, glm::radians(-columpiar), glm::vec3(0.0f, 0.0, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        asientoColDer.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-121.0f, 18.0f, 5.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        model = glm::rotate(model, glm::radians(columpiar), glm::vec3(0.0f, 0.0, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        asientoColIzq.Draw(shader);


        glBindVertexArray(0);
        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime+0.5);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime+0.5);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime+0.5);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime+0.5);
    }

    if (activanim)
    {   //Animar columpio
        if (columadel == true) {
            if (columpiar < 45.0) {
                columpiar += 1.0;
            }
            else {
                columadel = false;
            }
        }

        if (columadel == false) {
            if (columpiar > -45.0) {
                columpiar -= 1.0;
            }
            else {
                columadel = true;
            }
        }

        //Animar Figuras Cilindros
        if (girarCil == true) {
            if (cil < 5) {
                if (rotarCil < 360.0f) {
                    rotarCil += 1.0f;
                }
                cil += 1;
            }
            else {
                rotarCil = 360.0f;
                cil = 0;
                girarCil = false;
            }
        }

        if (girarCil == false) {
            if (cil < 5) {
                if (rotarCil > 0.0f) {
                    rotarCil -= 1.0f;
                }
                cil += 1;
            }
            else {
                rotarCil = 0.0f;
                cil = 0;
                girarCil = true;
            }
        }

        
    }

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }


    if (keys[GLFW_KEY_N])
    {
        activanim = true;
        columadel = true;
        girarCil = true;

    }

    if (keys[GLFW_KEY_M])
    {
        activanim = false;

    }
    
    if (keys[GLFW_KEY_Z]) {

        if (activanim == true) {
            movAdel = true;
            giroRueda = true;
        }
    }

    if (keys[GLFW_KEY_X]) {

        movAdel = false;
        giroRueda = false;
    }
}

void animaCompleja() {
    if(movAdel){
        if (recorrido1)
        {
            
            if (movKitZ > -80.0f) {
                movKitZ -= 0.5f;
                movKitZ2 -= 0.5f;
                movKitZ3 -= 0.5f;
                movKitZ4 -= 0.5f;
                movKitZ5 -= 0.5f;
                girar -= 2.0f;

            }
            else{
                recorrido1 = false;
                recorrido2 = true;
            }

        }
        if (recorrido2)
        {
            //Efecto de rotación
            if (rotKit > -90) {
                rotKit -= 1.0f;
                movKitZ -= 0.1f;
                movKitX += 0.1f;
                movKitZ2 -= 0.032f;
                movKitX2 += 0.115f;
                movKitZ3 -= 0.086f;
                movKitX3 += 0.168f;
                movKitZ4 -= 0.115f;
                movKitX4 += 0.032f;
                movKitZ5 -= 0.168f;
                movKitX5 += 0.086f;
                girar -= 2.0f;
            }
            else {
                recorrido2 = false;
                recorrido3 = true;
            }
              
        }

        if (recorrido3)
        {
            if (movKitX < 40.0f) {
                movKitX += 0.5f;
                movKitX2 += 0.5f;
                movKitX3 += 0.5f;
                movKitX4 += 0.5f;
                movKitX5 += 0.5f;
                girar -= 2.0f;
            }
            else {
                recorrido3 = false;
                recorrido4 = true;
            }
            
        }

       if (recorrido4)
        {
           //Efecto de rotación
            if (rotKit > -180) {
                rotKit -= 1.0f;
                movKitZ += 0.1f;
                movKitX += 0.1f;
                movKitZ2 += 0.115f;
                movKitX2 += 0.032f;
                movKitZ3 += 0.168f;
                movKitX3 += 0.086f;
                movKitZ4 += 0.032f;
                movKitX4 += 0.115f;
                movKitZ5 += 0.086f;
                movKitX5 += 0.168f;
                girar -= 2.0f;
            }
            else {
                recorrido4 = false;
                recorrido5 = true;
            }
        }

       if (recorrido5)
       {
           if (movKitZ < 10.0f) {
               movKitZ += 0.5f;
               movKitZ2 += 0.5f;
               movKitZ3 += 0.5f;
               movKitZ4 += 0.5f;
               movKitZ5 += 0.5f;
               girar -= 2.0f;
           }
           else {
               recorrido5 = false;
               recorrido6 = true;
           }

       }

       if (recorrido6)
       {
           //Efecto de rotación
           if (rotKit > -270) {
               rotKit -= 1.0f;
               movKitZ += 0.1f;
               movKitX -= 0.1f;
               movKitZ2 += 0.032f;
               movKitX2 -= 0.115f;
               movKitZ3 += 0.086f;
               movKitX3 -= 0.168f;
               movKitZ4 += 0.115f;
               movKitX4 -= 0.032f;
               movKitZ5 += 0.168f;
               movKitX5 -= 0.086f;
               girar -= 2.0f;
           }
           else {
               recorrido6 = false;
               recorrido7 = true;
           }
       }

       if (recorrido7)
       {
           if (movKitX > 9.0f) {
               movKitX -= 0.5f;
               movKitX2 -= 0.5f;
               movKitX3 -= 0.5f;
               movKitX4 -= 0.5f;
               movKitX5 -= 0.5f;
               girar -= 1.0f;
           }
           else {
               recorrido7 = false;
               recorrido8 = true;
           }

       }

       if (recorrido8)
       {
           //Efecto de rotación
           if (rotKit > -360) {
               rotKit -= 1.0f;
               movKitZ -= 0.1f;
               movKitX -= 0.1f;
               movKitZ2 -= 0.115f;
               movKitX2 -= 0.032f;
               movKitZ3 -= 0.168f;
               movKitX3 -= 0.086f;
               movKitZ4 -= 0.032f;
               movKitX4 -= 0.115f;
               movKitZ5 -= 0.086f;
               movKitX5 -= 0.168f;
               girar -= 2.0f;
           }
           else {
               rotKit = 0.0f;
               recorrido8 = false;
               recorrido1 = true;
             
           }
       }

    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}


