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
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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


    // VARIABLES WE GOTTA DEFINE AND STUFF
    const float verticies[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };

    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);


        // SHADERS ============================================================================

        // arg 1 is the number of strings we're passing in as source code.
        glShaderSource(vertexShader, 1, &vertexShaderSourceCode, NULL);
        glCompileShader(vertexShader);
        checkShaderCompilationSuccess(vertexShader);

        glShaderSource(fragmentShader, 1, &fragmentShaderSourceCode, NULL);
        glCompileShader(fragmentShader);
        checkShaderCompilationSuccess(fragmentShader);

        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        checkShaderLinkingSuccess(shaderProgram);

        glUseProgram(shaderProgram);
        //  ============================================================================

        glBindVertexArray(VAO);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // CLEANUP ========================================
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glfwTerminate();
    return 0;
}

