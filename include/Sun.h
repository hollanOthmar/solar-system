//
// Created by hollan haule on 1/2/19.
//

#ifndef CLIONPRO1_SUN_H
#define CLIONPRO1_SUN_H

#include "Renderable.h"
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>

class Sun: public Renderable {
public:
    Sun(float scale, glm::vec3& lightColor,glm::vec3& lightPos);
    ~Sun();
    virtual void init();
    virtual void update();
    virtual void draw(glm::mat4& view, glm::mat4& proj,glm::vec3& viewPos,Shader& shader);

protected:
    float m_scale;
    glm::vec3 m_sunColor;
    glm::vec3 m_position;
};


#endif //CLIONPRO1_SUN_H
