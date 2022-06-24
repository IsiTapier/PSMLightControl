/*
 NavBar.cpp - NavBar-Library for Librarys.
*/

#include "NavBar.h"
#include "../button/Button.h"
#include "../viewManager/ViewManager.h"

NavBar::NavBar(ContainerProperties properties, std::vector<Container*> content) : Container(properties, content) {
    setProperties(*getProperties().setLength(Size(1., 1))->setHeight(Size(.25, 1))->setInvisible(true)->setBorderThickness(Spacing(0, 0, 0, 4))->setBorderColor(TFT_WHITE));
}

void NavBar::init() {
    std::vector<Container*> pages;
    for(View* view : ViewManager::getViews()) {
        Button* button = new Button(ContainerProperties(Size(70), Size(70), Spacing(3), Spacing(0), Spacing(2), Size(4)), ButtonProperties(), 
            [view](){ViewManager::setCurrentView(view->getId());return 0;},
            {new Text(ContainerProperties(), TextProperties(), view->getViewProperties().getName())}
        );
        addContent(button, true);
    }
}

