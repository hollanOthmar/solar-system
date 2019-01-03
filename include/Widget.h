//
// Created by hollan haule on 12/30/18.
//

#ifndef CLIONPRO1_WIDGET_H
#define CLIONPRO1_WIDGET_H

#include <iostream>

class Widget {
public:
    std::string getName();
    Widget(std::string name = "no name");
    Widget(const Widget& rhs);//copy constructor
    ~Widget();
    Widget& operator = (Widget& rhs);//copy operator

private:
    std::string m_name;
};


#endif //CLIONPRO1_WIDGET_H
