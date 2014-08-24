g++ -IC:\repos\glew-1.11.0\include -c -o hello.o hello.cpp
g++ -LC:\repos\glew-1.11.0\lib -o hello.exe hello.o -lglew32 -lopengl32 -lmingw32 -lSDL2main -lSDL2
hello.exe