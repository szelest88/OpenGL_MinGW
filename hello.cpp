#include <GL/glew.h> // has to be included before SDL

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <iostream>

#include "BmpObject.h" // for BMP loading

#define GLM_FORCE_RADIANS // has to be defined before glm includes in order to avoid compile-time warnings
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>

const GLchar* vertexShaderSource =
 "#version 150 core\n"
 "in vec3 color;"
 "out vec3 Color;"
 "in vec2 texcoord;"
 "out vec2 Texcoord;"
 "in vec2 position;"
 
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 proj;"

 "void main() {"
 "Color = color;"
 " Texcoord = texcoord;"
 " gl_Position = proj*view*model * vec4(position, 0.0, 1.0);"
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
     -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // Vertex 1 (X, Y)
     0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // Vertex 2 (X, Y)
     -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  // Vertex 3 (X, Y)
     0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // Vertex 1 (X, Y)
     -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // Vertex 2 (X, Y)
     0.5f, 0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f  // Vertex 3 (X, Y)
};
float vertices2[] = {
     0.1f+-0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // Vertex 1 (X, Y)
     0.1f+0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // Vertex 2 (X, Y)
     0.1f+-0.5f, 0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  // Vertex 3 (X, Y)
     0.1f+0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // Vertex 1 (X, Y)
     0.1f+-0.5f, 0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // Vertex 2 (X, Y)
     0.1f+0.5f, 0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f  // Vertex 3 (X, Y)
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
/*
unsigned char pixels[] = 
{   
      0,    0,  255,          0,    0,  255,        0,    0,  255,       155,  155,  0,
      0,    0,  255,          0,    0,  255,        0,    0,  255,       155,  155,  0,
      0,    0,  255,          0,    0,  255,        0,    0,  255,       155,  155,  0,
    155,  140,  240,        185,  185,    0,        155, 155,  0,          0,  155,  0
};
*/
// or load...
BmpObject* bmpObject = new BmpObject("LenaRGB.bmp");
unsigned char* pixels = bmpObject->data;
cout<<"\n\nPixels: "<<bmpObject->width;
int textureWidth  = bmpObject->width;
int textureHeight = bmpObject->height;
glTexImage2D(
    GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, 
    pixels);

GLuint vertexArrayObject; // now test if glew has been initialized correctly
glGenVertexArrays(1, &vertexArrayObject);
glBindVertexArray(vertexArrayObject);

GLuint vbo;
glGenBuffers(1, &vbo);

glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


//
GLuint vertexArrayObject2; // now test if glew has been initialized correctly
glGenVertexArrays(1, &vertexArrayObject2);
glBindVertexArray(vertexArrayObject2);

GLuint vbo2;
glGenBuffers(1, &vbo2);

glBindBuffer(GL_ARRAY_BUFFER, vbo2);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

//
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

GLuint shaderProgram2 = glCreateProgram();
glAttachShader(shaderProgram2, vertexShader);
glAttachShader(shaderProgram2, fragmentShader);
glBindFragDataLocation(shaderProgram2, 0, "outColor");
glLinkProgram(shaderProgram2);

// attribute variables

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

// uniform variables
glm::mat4 proj;
proj = glm::perspective(45.0f, 800.0f/600.0f, 1.0f, 100.0f);

GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

glm::mat4 view;
view = glm::lookAt(
    glm::vec3(1.0f, -1.0f, 1.2f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f)
    
    );

GLint uniView = glGetUniformLocation(shaderProgram, "view");
glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));


glm::mat4 model;
model = glm::rotate(model, 45.0f*3.1415f/180.0f, glm::vec3(0.0f, 0.0f, 1.0f));


GLint uniModel;
//2:
// attribute variables

GLint posAttrib2 = glGetAttribLocation(shaderProgram2, "position");
glEnableVertexAttribArray(posAttrib2);

GLint colAttrib2 = glGetAttribLocation(shaderProgram2, "color");
glEnableVertexAttribArray(colAttrib2);

GLint texAttrib2 = glGetAttribLocation(shaderProgram2, "texcoord");
glEnableVertexAttribArray(texAttrib2);

glVertexAttribPointer(posAttrib2, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);

glVertexAttribPointer(colAttrib2, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), 
    (void*)(2*sizeof(float)));

glVertexAttribPointer(texAttrib2, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 
    (void*)(5*sizeof(float)));

// uniform variables
glm::mat4 proj2;
proj2 = glm::perspective(45.0f, 800.0f/600.0f, 1.0f, 100.0f);

GLint uniProj2 = glGetUniformLocation(shaderProgram2, "proj");
glUniformMatrix4fv(uniProj2, 1, GL_FALSE, glm::value_ptr(proj2));

glm::mat4 view2;
view2 = glm::lookAt(
    glm::vec3(1.0f, -1.0f, 1.2f),
    glm::vec3(0.0f, 0.3f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f)
    
    );

GLint uniView2 = glGetUniformLocation(shaderProgram2, "view");
glUniformMatrix4fv(uniView2, 1, GL_FALSE, glm::value_ptr(view2));

glm::mat4 model2;
model2 = glm::rotate(model2, 45.0f*3.1415f/180.0f, glm::vec3(0.0f, 0.0f, 1.0f));

GLint uniModel2;
//uniModel = glGetUniformLocation(shaderProgram, "model");
//glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

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

glUseProgram(shaderProgram);

model = glm::rotate(model, 0.005f*3.1415f/180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
uniModel = glGetUniformLocation(shaderProgram, "model");
glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 3);

glUseProgram(shaderProgram2);

model2 = glm::rotate(model2, 0.005f*3.1415f/180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
uniModel2 = glGetUniformLocation(shaderProgram2, "model");

glUniformMatrix4fv(uniModel2, 1, GL_FALSE, glm::value_ptr(model2));


glBindVertexArray(vertexArrayObject2);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(window);
}

glDeleteProgram(shaderProgram);
glDeleteProgram(shaderProgram2);

glDeleteShader(fragmentShader);
glDeleteShader(vertexShader);

SDL_GL_DeleteContext(context);

SDL_Quit();
    return 0;
}