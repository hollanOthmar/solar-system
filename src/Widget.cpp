//
// Created by hollan haule on 12/30/18.
//

#include "../include/Widget.h"
#include <iostream>

Widget::Widget(std::string name):m_name(name) {}
std::string Widget::getName() { return m_name;}