//
// Created by hollan haule on 1/1/19.
//

#ifndef CLIONPRO1_RENDERABLE_H
#define CLIONPRO1_RENDERABLE_H

#include "renderUtility.h"
#include "shader.hpp"
#include "camera.hpp"
//#include "Renderer.h"

class Renderable {
public:
//    Renderable();
//    virtual ~Renderable();
//    virtual void render(Camera& camera) = 0;
    virtual void init() = 0;
//    virtual void update(Shader& shader) = 0;
    virtual void draw(glm::mat4& view, glm::mat4& proj,glm::vec3& viewPos,Shader& shader) = 0;

protected:
    glm::mat4 model;
//    Renderer* renderer;
};


#endif //CLIONPRO1_RENDERABLE_H
