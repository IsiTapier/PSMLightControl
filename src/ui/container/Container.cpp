/*
 Container.cpp - Container-Library for Librarys.
*/

#include "Container.h"
#include "../viewManager/ViewManager.h"

//temporary
Container::Container() : _properties(ContainerProperties(0, 0)) {}


Container::Container(ContainerProperties properties, std::vector<Container*> content) : _properties(properties), _content(content) {
    // for(Container* content : _content) {
    //     //set dimensions
    //     ContainerProperties properties = content->getPorperties();
    //     properties.getLength().setReference(_properties.getLength(), false);
    //     properties.getHeight().setReference(_properties.getHeight(), false);
    //     properties.getPadding().setReference(properties.getLength(), properties.getHeight(), false);
    //     properties.getMargin().setReference(properties.getLength(), properties.getHeight(), false);
    //     properties.getBorderThickness().setReference(properties.getLength(), false);
    //     properties.getBorderRoundness().setReference(properties.getBorderThickness(), false);
    //     content->setProperties(properties);
    // }
    for(Container* content : _content)
        content->setProperties(*content->getPorperties().setId(_properties.getNextId()));
}

void Container::init() {
    Spacing margin = _properties.getMargin();
    short x = _properties.getX()+_properties.getBorderThickness();;
    short y = _properties.getY()+_properties.getBorderThickness();;
    short currentX = 0;
    short currentY = 0;
    short nextY = 0;
    short paddingLeft = margin.get(LEFT);
    short paddingTop = margin.get(TOP);
    short paddingBottom = 0;
    byte place = 0;
    for(Container* content : _content) {
        //set dimensions
        ContainerProperties properties = content->getPorperties();
        Spacing padding = properties.getPadding();
        CONTAINER_SET_REFERENCES(_properties)
        properties.setOrder(_properties.getOrder()+(properties.getInvisible()?0:1));
        properties.setViewId(_properties.getViewId());
        place++;
        //check if available length in current line is enough
        if(_properties.getContentLength()-currentX < properties.getLength() + MAX(paddingLeft, padding.get(LEFT)) + MAX(padding.get(RIGHT), margin.get(RIGHT))) {
            //check if available length in new line is enough
            if(_properties.getContentLength() < properties.getLength() + MAX(margin.get(LEFT), padding.get(LEFT)) + MAX(padding.get(RIGHT), margin.get(RIGHT))) {
                if(DEBUG)
                    Serial.println("WARNING:\tContainer skipped, because it was longer than its parent-container");
                properties.setDraw(false);
                content->setProperties(properties);
                continue;
            }
            //check if available height is enough
            if(_properties.getContentHeight()-currentY-nextY < properties.getHeight() + MAX(padding.get(TOP), paddingBottom) + MAX(padding.get(BOTTOM), margin.get(BOTTOM))) {
                if(DEBUG)
                    Serial.println("WARNING:\tContainer skipped, because there wasn't enough height available");
                properties.setDraw(false);
                content->setProperties(properties);
                continue;
            }
            //set new line
            paddingTop = paddingBottom;
            paddingBottom = 0;
            currentX = 0;
            currentY += nextY;
            nextY = 0;
            paddingLeft = margin.get(LEFT);
        }
        //check if available height is enough
        if(_properties.getContentHeight()-currentY < properties.getHeight() + MAX(padding.get(TOP), paddingTop) + MAX(padding.get(BOTTOM), margin.get(BOTTOM))) {
            if(DEBUG)
                Serial.println("WARNING:\tContainer skipped, because there wasn't enough height available");
            properties.setDraw(false);
            content->setProperties(properties);
            continue;
        }
        //draw content
        properties.setDraw(true);
        properties.setXY(x+currentX+MAX(paddingLeft, padding.get(LEFT)), y+currentY+MAX(padding.get(TOP), paddingTop));
        content->setProperties(properties);
        content->init();
        
        //set paddings for next content
        SETMAX(nextY, MAX(paddingTop, padding.get(TOP))+properties.getHeight())
        SETMAX(paddingBottom, padding.get(BOTTOM) - nextY+MAX(paddingTop, padding.get(TOP))+properties.getHeight()) //partly saving space if allready a larger container with less padding there
        currentX += MAX(paddingLeft, padding.get(LEFT)) + properties.getLength();
        paddingLeft = padding.get(RIGHT);
    }
}

//TODO fill available heights
void Container::draw() {
    if(!_properties.getDraw())
        return;
    //draw border
    drawBorder();
    //draw contents
    for(Container* content : _content)
        content->draw();
}

void Container::drawBorder(bool erase) {
    if(!_properties.getDraw())
        return;
    if(erase)
        display.fillRoundRect(_properties.getX(), _properties.getY(), _properties.getLength(), _properties.getHeight(), _properties.getBorderRoundness(), getColor());
    if(_properties.getInvisible())
        return;
    //draw border
    short borderThickness = _properties.getBorderThickness();
    /*for(short i = 0; i < borderThickness; i++) {
        display.drawRoundRect(x+i, y+i, _properties.getLength()-2*i, _properties.getHeight()-2*i, MAX(0, _properties.getBorderRoundness()-i), _properties.getBorderColor());
    }*/
    display.fillRoundBorder(_properties.getX(), _properties.getY(), _properties.getLength(), _properties.getHeight(), _properties.getBorderThickness(), _properties.getBorderRoundness(), IFNOT(_properties.getBorderColor(), NO_COLOR, ColorManager::getBorderColor()));
    //display.fillRoundRect(x, y, _properties.getLength(), _properties.getHeight(), _properties.getBorderRoundness(), _properties.getBorderColor());
    //draw interior
    display.fillRoundRect(_properties.getX()+borderThickness, _properties.getY()+borderThickness, _properties.getLength()-2*borderThickness, _properties.getHeight()-2*borderThickness, MAX(0, _properties.getBorderRoundness()-borderThickness), getColor());
    //draw contents
}

ContainerProperties Container::getPorperties() {
    return _properties;
}

void Container::setProperties(ContainerProperties properties) {
    _properties = properties;
}

void Container::setBackground(uint16_t color) {
    _properties.setBackgroundColor(color);
    for(Container* content : _content)
        if(content->getPorperties().getInvisible())
            content->setBackground(color);
}

uint16_t Container::getColor() {
    return IFNOT(getPorperties().getBackgroundColor(), NO_COLOR, ColorManager::getContainerColor(getPorperties().getOrder()));
}

void Container::addContent(Container* content) {
    content->setProperties(*content->getPorperties().setId(_properties.getNextId()));
    _content.push_back(content);
    if(!_properties.getDraw())
        return;
    init();
    if(ViewManager::getCurrentView() == _properties.getViewId())
        draw();
}

void Container::removeContent(byte id) {
    Container* content = getContent(id);
    if(content == NULL)
        return;
    content->setProperties(*content->getPorperties().setDraw(false));
    _content.erase(getIterator(id));
    if(!_properties.getDraw())
        return;
    init();
    if(ViewManager::getCurrentView() == _properties.getViewId()) {
        drawBorder(true);
        draw();
    }
}

uint8_t Container::getContentAmount() {
    return _content.size();
}

void Container::setContentProperties(ContainerProperties properties) {
    for(Container* content : _content)
        content->setProperties(properties);
}

Container* Container::getContent(byte id) {
    if(id > _properties.getCurrentId())
        return NULL;
    for(Container* content : _content)
        if(content->getPorperties().getId() == id)
            return content;
    return NULL;
}

std::vector<Container*>::iterator Container::getIterator(byte id) {
    if(id > _properties.getCurrentId())
        return _content.end();
    std::vector<Container*>::iterator it = _content.begin();
    for(it; it != _content.end(); ++it)
        if((*it)->getPorperties().getId() == id)
            return it;
    return _content.end();
}