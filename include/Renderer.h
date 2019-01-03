//
// Created by hollan haule on 1/2/19.
//

#ifndef CLIONPRO1_RENDERER_H
#define CLIONPRO1_RENDERER_H

#include <iostream>
#include <vector>
#include "renderUtility.h"


class Renderer {
public:
    Renderer(std::vector<Vertex>& vertices);
    ~Renderer();
    void init();
    void render();
    void genVAO();
    void bindVAO(unsigned int vao_);
    void bindVBO(unsigned int vbo_);
    unsigned int getVAO();
    unsigned int getVBO();
protected:
    std::vector<Vertex> m_data;
    unsigned int vao,vbo;
};


#endif //CLIONPRO1_RENDERER_H
