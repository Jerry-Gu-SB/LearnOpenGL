#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// SHADER:

static auto vertexShaderSourceCode = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main () \n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

static auto fragmentShaderSourceCode = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 0.1f, 0.3f, 0.5f);\n"
    "}\0";

static auto fragmentShaderBLUESourceCode = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(0.25f, 0.25f, 0.9f, 0.5f);\n"
    "}\0";

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void checkShaderCompilationSuccess(const unsigned int vertexShaderID) {
    int success;
    char infoLog[512];

    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

static void checkShaderLinkingSuccess(const unsigned int shaderProgramID) {
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderProgramID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

static void processInput(GLFWwindow * window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        glClearColor(0.2f, 0.3f, .9f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glClearColor(0.9f, 0.3f, .1f, 1.0f);
    }
}

int main()
{

    // SETUP ==========================================================================================


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // if OpenGL and GLFW were restaurant, OpenGL would be the kitchen and GLFW would be the building and outer exterior
    GLFWwindow* window = glfwCreateWindow(800, 600, "glfw window", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // so it looks like GLAD is what actually manages your GPU memory and connects the function calls into actual
    // GPU work
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to inialize GLAD" << std::endl;
    }

    // so we're setting the callback function and passing in the window object we've made
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // VERTICES =========================================================================
    const float verticies[] = {
         0.5f,  0.5f, 0.0f,   // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,    // top left
         0.0f,  0.95f,0.0f  // top center point
    };

    const int indices[] = {
        0, 1, 3,
        1, 2, 3,
        1, 2, 4
    };

    // BUFFER OBJECTS ==================================================================

    // index data of the indices above
    unsigned int elementBufferObject;
    // Just generates an ID. index 0: the number of object NAMES to generate, index 2: where to store the ID
    glGenBuffers(1, &elementBufferObject);

    // This is the actual data storage object of raw, unstructured, numbers
    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);

    unsigned int vertexBufferObject_2;
    glGenBuffers(1, &vertexBufferObject_2);

    // VAO stores the GPU/driver state config
    unsigned int vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);

    unsigned int vertexArrayObject_2;
    glGenVertexArrays(1, &vertexArrayObject_2);

    // Configure Vertex Array Object
    glBindVertexArray(vertexArrayObject); // Bind the VAO to say "this is what we're touching"

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);  // Bind the actual data we're about to touch
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);  // load vertices

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);  // Bind the indices object now
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);  // load indices

    // This is tells OpenGL how to interpret the vertex data that's bound in the VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Configure second VAO
    glBindVertexArray(vertexArrayObject_2); // Bind the VAO to say "this is what we're touching"

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_2);  // Bind the actual data we're about to touch
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);  // load vertices

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);  // Bind the indices object now
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);  // load indices

    // This is tells OpenGL how to interpret the vertex data that's bound in the VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // SHADERS ============================================================================
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    unsigned int fragmentShaderBLUE;
    fragmentShaderBLUE = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSourceCode, NULL); // arg 1 is the number of strings we're passing in as source code.
    glCompileShader(vertexShader);
    checkShaderCompilationSuccess(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCode, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilationSuccess(fragmentShader);

    glShaderSource(fragmentShaderBLUE, 1, &fragmentShaderBLUESourceCode, NULL);
    glCompileShader(fragmentShaderBLUE);
    checkShaderCompilationSuccess(fragmentShaderBLUE);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkShaderLinkingSuccess(shaderProgram);

    // blue shader program:
    unsigned int blueShaderProgram;
    blueShaderProgram = glCreateProgram();
    glAttachShader(blueShaderProgram, vertexShader);
    glAttachShader(blueShaderProgram, fragmentShaderBLUE);
    glLinkProgram(blueShaderProgram);
    checkShaderLinkingSuccess(blueShaderProgram);


    // RENDER LOOP ===========================================================================
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArrayObject);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 3));

        glUseProgram(blueShaderProgram);
        glBindVertexArray(vertexArrayObject_2);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // CLEANUP ========================================
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glfwTerminate();
    return 0;
}

