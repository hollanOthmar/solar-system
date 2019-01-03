//
// Created by hollan haule on 1/2/19.
//

#include "Planet.h"
Planet::Planet(float scale,glm::vec3& lightColor,glm::vec3& lightPos,float orbit):
        m_scale(scale),m_lightColor(lightColor),m_lightPosition(lightPos),m_orbit(orbit)
{
    model = glm::mat4(1.0f);
    m_position = glm::vec3(0.0,0.0,m_orbit);
    m_planetColor = glm::vec3(0.0,0.0,1.0);
}

void Planet::init(){
//    model = glm::scale(model,glm::vec3(m_scale,m_scale,m_scale));
//    model = glm::translate(model,m_position);
//    model = glm::scale(model,glm::vec3(m_scale));
    model = glm::scale(model, glm::vec3(m_scale));
    model = glm::translate(model,m_position);
}

void Planet::draw(glm::mat4& view, glm::mat4& proj,glm::vec3& viewPos, Shader& shader)
{
    shader.use();

//    model = glm::translate(model,m_position);
//    model = glm::scale(model,glm::vec3(m_scale,m_scale,m_scale));
    shader.setMat4f("model",model);

    shader.setMat4f("view",view);
    shader.setMat4f("projection",proj);
    shader.setVec3f("lightColor",m_lightColor);
    shader.setVec3f("lightPos",m_lightPosition);
    shader.setVec3f("viewPos", viewPos);
    shader.setVec3f("objectColor",m_planetColor);
    //normal matrix for object!
    //glm::mat4 normalMatrix = glm::inverse(model);
    glm::mat4 normalMatrix = glm::inverseTranspose(model);
//    normalMatrix = glm::transpose(normalMatrix);
    shader.setMat4f("normalMatrix",normalMatrix);
}

void Planet::update(float dt) {
    model = glm::mat4(1.0f);
    double objX   = sin(glfwGetTime()) * m_orbit;
    double objZ   = cos(glfwGetTime()) * m_orbit;
    m_position = glm::vec3(objX,0.0f,objZ);

    model = glm::scale(model, glm::vec3(m_scale));
    model = glm::translate(model,m_position);

}
Planet::~Planet(){}