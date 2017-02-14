#ifndef GUARD_MESH_H
#define GUARD_MESH_H

#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex {
public:
    Vertex() {
        pos = glm::vec3(0, 0, 0);
    }

    Vertex(const glm::vec3 &pos) {
        this->pos = pos;
    }

    void Vertex::set_vec(const glm::vec3 &pos) {
        this->pos = pos;
    }

private:
    glm::vec3 pos;
};

class Mesh {
public:
    Mesh(Vertex *verticies, unsigned int numVertices);

    ~Mesh();

    void Draw();

private:

    enum {
        POSITION_VB,
        NUM_BUFFERS
    };
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];

    unsigned int m_drawCount;
};

#endif
