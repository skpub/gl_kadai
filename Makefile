LIBPNG_CXXFLAGS = $(shell libpng-config --cppflags)
LIBPNG_LDFLAGS  = $(shell libpng-config --ldflags)

app: main.o object_loader.o material_loader.o
	g++ -o app main.o object_loader.o material_loader.o $(LIBPNG_CXXFLAGS) $(LIBPNG_LDFLAGS) -lglut -lGLU -lGL -lm

main.o: main.cpp
	g++ -c main.cpp

object_loader.o: object_loader.cpp
	g++ -c object_loader.cpp

material_loader.o: material_loader.cpp
	g++ -c material_loader.cpp

clean:;	rm -f *.o


