CXX = g++
CXXFLAGS = -std=c++11

all: main.o Display.o Mesh.o Shader.o
	$(CXX) $^ -o main $(CXXLIBS)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGES) -c $< -o $@

clean:
	rm main
	rm *.o
