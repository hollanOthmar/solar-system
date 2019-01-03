//
// Created by hollan haule on 1/2/19.
//

#include "Renderer.h"
Renderer::Renderer(std::vector<Vertex>& vertices):m_data(vertices) {}

//this function is called by the user!
void Renderer::init()
{
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,m_data.size()* sizeof(Vertex),&m_data[0],GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glBindVertexArray(0);
}

void Renderer::render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES,0,3*m_data.size());
}

void Renderer::genVAO(){
    glGenVertexArrays(1,&vao);
};
void Renderer::bindVAO(unsigned int vao_){
    glBindVertexArray(vao_);
};
void Renderer::bindVBO(unsigned int vbo_){
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
};
unsigned int Renderer::getVAO(){
    return vao;
}
unsigned int Renderer::getVBO(){
    return vbo;
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}