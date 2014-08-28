
g++ -IC:\repos\glew-1.11.0\include -c  hello.cpp 
g++ -c BmpObject.cpp

g++ -LC:\repos\glew-1.11.0\lib -o hello.exe BmpObject.o hello.o -lglew32 -lopengl32 -lmingw32 -lSDL2main -lSDL2

 hello.exe
