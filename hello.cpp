#include <GL/glew.h> // has to be included before SDL

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <iostream>

const GLchar* vertexShaderSource =
 "#version 150 core\n"
 "in vec3 color;"
 "out vec3 Color;"
 "in vec2 texcoord;"
 "out vec2 Texcoord;"
 "in vec2 position;"
 "void main() {"
 "Color = color;"
 " Texcoord = texcoord;"
 " gl_Position = vec4(position, 0.0, 1.0);"
 "}";

 const GLchar* fragmentShaderSource =
 "#version 150 core\n"
 "in vec3 Color;"
 "in vec2 Texcoord;"
 "out vec4 outColor;"
 "uniform sampler2D tex;"
 "void main() {"
     "   outColor = texture(tex, Texcoord)*vec4(Color, 1.0);"
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
     0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // Vertex 1 (X, Y)
     1.0f, 0.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // Vertex 2 (X, Y)
     0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // Vertex 3 (X, Y)
     1.0f, 0.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // Vertex 1 (X, Y)
     0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // Vertex 2 (X, Y)
     1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f  // Vertex 3 (X, Y)
};

GLuint tex;
glGenTextures(1, &tex);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
float color[]={ 0.0f, 0.0f, 0.0f, 1.0f };
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // LINEAR causes sort of blurry appearance

glGenerateMipmap(GL_TEXTURE_2D);

unsigned char pixels[] = 
{   
      0,    0,  255,          0,    0,  255,        0,    0,  255,       155,  155,  0,
      0,    0,  255,          0,    0,  255,        0,    0,  255,       155,  155,  0,
      0,    0,  255,          0,    0,  255,        0,    0,  255,       155,  155,  0,
    155,  140,  240,        185,  185,    0,        155, 155,  0,          0,  155,  0
};
// or load...
int textureWidth  = 4;
int textureHeight = 4;
glTexImage2D(
    GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 
    pixels);

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

GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
glEnableVertexAttribArray(colAttrib);

GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
glEnableVertexAttribArray(texAttrib);

glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);

glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), 
    (void*)(2*sizeof(float)));

glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 
    (void*)(5*sizeof(float)));

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