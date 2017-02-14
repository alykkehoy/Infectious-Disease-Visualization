#include "Mesh.h"

Mesh::Mesh(Vertex *verticies, unsigned int numVerticess) {
    m_drawCount = numVerticess;

    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVerticess * sizeof(verticies[0]), verticies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}


Mesh::~Mesh() {
    glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
    glBindVertexArray(m_vertexArrayObject);

    glDrawArrays(GL_POINTS, 0, m_drawCount);

    glBindVertexArray(0);
}

