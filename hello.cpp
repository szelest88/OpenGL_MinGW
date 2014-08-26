#include <GL/glew.h> // has to be included before SDL

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <iostream>

const GLchar* vertexShaderSource =
 "#version 150 core\n"
 "in vec2 position;"
 "void main() {"
 " gl_Position = vec4(position, 0.0, 1.0);"
 "}";

 const GLchar* fragmentShaderSource =
 "#version 150 core\n"
 "out vec4 outColor;"
 "void main() {"
 " outColor = vec4(1.0, 1.0, 0.0, 0.5);"
 "}";

 
int main(int argc, char* argv[]) {

SDL_Init(SDL_INIT_VIDEO);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);



SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

SDL_GLContext context = SDL_GL_CreateContext(window);

glewExperimental = GL_TRUE;
glewInit(); // has to be initialized after creating a window and the context

float vertices[] = {
     0.0f,  0.5f, // Vertex 1 (X, Y)
     0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f,  // Vertex 3 (X, Y)
     0.0f, 0.5f+0.5f, // Vertex 1 (X, Y)
     0.5f, 0.5f-0.5f, // Vertex 2 (X, Y)
    -0.5f, 0.5f-0.5f  // Vertex 3 (X, Y)
};


GLuint vertexArrayObject; // now test if glew has been initialized correctly
glGenVertexArrays(1, &vertexArrayObject);
glBindVertexArray(vertexArrayObject);

GLuint vbo;
glGenBuffers(1, &vbo);

glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);

GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);

GLuint shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glBindFragDataLocation(shaderProgram, 0, "outColor");
glLinkProgram(shaderProgram);
glUseProgram(shaderProgram);

GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
glEnableVertexAttribArray(posAttrib);
glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

SDL_Event windowEvent;
while(true){
    if(SDL_PollEvent(&windowEvent))
    {
        if (
            windowEvent.type == SDL_QUIT
            ||
            windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE
            ) break;
    }

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    SDL_GL_SwapWindow(window);
}

glDeleteProgram(shaderProgram);
glDeleteShader(fragmentShader);
glDeleteShader(vertexShader);

SDL_GL_DeleteContext(context);

SDL_Quit();
    return 0;
}