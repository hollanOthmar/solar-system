//
// Created by hollan haule on 1/2/19.
//

#include "Sun.h"
Sun::Sun(float scale, glm::vec3 &lightColor, glm::vec3 &lightPos)
        :m_scale(scale),m_sunColor(lightColor),m_position(lightPos)
        {
            model = glm::mat4(1.0f);
        }
void Sun::init(){
    model = glm::scale(model, glm::vec3(m_scale));
}
void Sun::draw(glm::mat4& view, glm::mat4& proj,glm::vec3& viewPos,Shader& shader)
{
    shader.use();
    model = glm::translate(model, m_position);
//    model = glm::scale(model, glm::vec3(0.2f));
    shader.setMat4f("model",model);
    shader.setMat4f("view",view);
    shader.setMat4f("projection",proj);
}
void Sun::update() {
    std::cout << "Nothing for now!...\n";
}

Sun::~Sun(){};