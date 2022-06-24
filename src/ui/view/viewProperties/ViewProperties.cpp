/*
 ViewProperties.cpp - ViewProperties-Library for Librarys.
*/

#include "viewProperties.h"

ViewProperties::ViewProperties(String name) : _name(name)  {

}

String ViewProperties::getName() {
    return _name;
}