/*
 NavBar.cpp - NavBar-Library for Librarys.
*/

#include "NavBar.h"

NavBar::NavBar(ContainerProperties properties, std::vector<Container*> content) : Container(properties, content) {
    setProperties(*getPorperties().setLength(Size(1., 1))->setHeight(Size(.2, 1))->setInvisible(true)->setBorderThickness(2)->setBorderColor(TFT_WHITE));
}