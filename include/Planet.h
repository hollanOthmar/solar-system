//
// Created by hollan haule on 1/2/19.
//

#ifndef CLIONPRO1_PLANET_H
#define CLIONPRO1_PLANET_H

#include "Renderable.h"
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>

class Planet: public Renderable {
public:
    Planet(float scale,glm::vec3& lightColor,glm::vec3& lightPos,float orbit);
    virtual ~Planet();
//    virtual void render(Camera& camera);
//    virtual void update(Shader& shader);
    virtual void init();
    virtual void draw(glm::mat4& view, glm::mat4& proj,glm::vec3& viewPos,Shader& shader);
    virtual void update(float dt);

private:
    float m_scale;
    float m_orbit;
    glm::vec3 m_planetColor;
    glm::vec3 m_lightPosition;
    glm::vec3 m_lightColor;
    glm::vec3 m_position;
};


#endif //CLIONPRO1_PLANET_H
