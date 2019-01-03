//
// Created by hollan haule on 1/1/19.
//

#ifndef CLIONPRO1_RENDERUTILITY_H
#define CLIONPRO1_RENDERUTILITY_H

#define GLM_ENABLE_EXPERIMENTAL
#include "glad/glad.h"
#include <glm/glm.hpp>
//#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtc/matrix_inverse.hpp>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
};

#endif //CLIONPRO1_RENDERUTILITY_H
