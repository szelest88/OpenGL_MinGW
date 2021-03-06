#include <GL/glew.h> // has to be included before SDL

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[]) {

SDL_Init(SDL_INIT_VIDEO);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);



SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

SDL_GLContext context = SDL_GL_CreateContext(window);

glewExperimental = GL_TRUE;
glewInit(); // has to be initialized after creating a window and the context

GLuint vertexBuffer; // now test if glew has been initialized correctly
glGenBuffers(1, &vertexBuffer);

std::cout<<vertexBuffer;

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

    SDL_GL_SwapWindow(window);
}

SDL_GL_DeleteContext(context);

SDL_Quit();
    return 0;
}