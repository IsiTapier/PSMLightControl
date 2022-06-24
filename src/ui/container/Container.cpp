/*
 Container.cpp - Container-Library for Librarys.
*/

#include "Container.h"
#include "../viewManager/ViewManager.h"

//temporary
Container::Container() : _properties(ContainerProperties(0, 0)) {}


Container::Container(ContainerProperties properties, std::vector<Container*> content) : _properties(properties), _content(content) {
    for(Container* content : _content)
        content->setProperties(*content->getProperties().setId(_properties.getNextId()));
}

void Container::init() {
    Spacing padding = _properties.getPadding();
    short x = _properties.getContentX();
    short y = _properties.getContentY();
    short currentX = 0;
    short currentY = 0;
    short nextY = 0;
    short marginLeft = padding.get(LEFT);
    short marginTop = padding.get(TOP);
    short marginBottom = 0;
    byte place = 0;
    for(Container* content : _content) {
        //set dimensions
        ContainerProperties properties = content->getProperties();
        Spacing margin = properties.getMargin();
        CONTAINER_SET_REFERENCES(_properties)
        properties.setOrder(_properties.getOrder()+(properties.getInvisible()?0:1));
        properties.setViewId(_properties.getViewId());
        place++;
        //check if available length in current line is enough
        if(_properties.getContentLength()-currentX < properties.getLength() + MAX(marginLeft, margin.get(LEFT)) + MAX(margin.get(RIGHT), padding.get(RIGHT))) {
            //check if available length in new line is enough
            if(_properties.getContentLength() < properties.getLength() + MAX(padding.get(LEFT), margin.get(LEFT)) + MAX(margin.get(RIGHT), padding.get(RIGHT))) {
                if(DEBUG)
                    Serial.println("WARNING:\tContainer skipped, because it was longer than its parent-container");
                properties.setDraw(false);
                content->setProperties(properties);
                continue;
            }
            //check if available height is enough
            if(_properties.getContentHeight()-currentY-nextY < properties.getHeight() + MAX(margin.get(TOP), marginBottom) + MAX(margin.get(BOTTOM), padding.get(BOTTOM))) {
                if(DEBUG)
                    Serial.println("WARNING:\tContainer skipped, because there wasn't enough height in the next line available");
                properties.setDraw(false);
                content->setProperties(properties);
                continue;
            }
            //set new line
            marginTop = marginBottom;
            marginBottom = 0;
            currentX = 0;
            currentY += nextY;
            nextY = 0;
            marginLeft = padding.get(LEFT);
        }
        //check if available height is enough
        if(_properties.getContentHeight()-currentY < properties.getHeight() + MAX(margin.get(TOP), marginTop) + MAX(margin.get(BOTTOM), padding.get(BOTTOM))) {
            if(DEBUG)
                Serial.println("WARNING:\tContainer skipped, because there wasn't enough height available.");
            properties.setDraw(false);
            content->setProperties(properties);
            continue;
        }
        //draw content
        properties.setDraw(true);
        properties.setXY(x+currentX+MAX(marginLeft, margin.get(LEFT)), y+currentY+MAX(margin.get(TOP), marginTop));
        content->setProperties(properties);
        content->init();
        
        //set margins for next content
        SETMAX(nextY, MAX(marginTop, margin.get(TOP))+properties.getHeight())
        SETMAX(marginBottom, margin.get(BOTTOM) - nextY+MAX(marginTop, margin.get(TOP))+properties.getHeight()) //partly saving space if allready a larger container with less margin there
        currentX += MAX(marginLeft, margin.get(LEFT)) + properties.getLength();
        marginLeft = margin.get(RIGHT);
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
    xSemaphoreTake(sync_display, portMAX_DELAY);
    if(erase)
        display.fillRoundRect(_properties.getX(), _properties.getY(), _properties.getLength(), _properties.getHeight(), _properties.getBorderRoundness(), getColor());

    if(!_properties.getDraw()) {
        xSemaphoreGive(sync_display);
        return;
    }
    
    Spacing border = _properties.getBorderThickness();
        
    //draw border
    display.fillRoundBorder(_properties.getX(), _properties.getY(), _properties.getLength(), _properties.getHeight(), border, _properties.getBorderRoundness(), IFNOT(_properties.getBorderColor(), NO_COLOR, ColorManager::getBorderColor()));
    // draw interior
    display.fillRoundRect(_properties.getContentX(), _properties.getContentY(), _properties.getContentLength(), _properties.getContentHeight(), MAX(0, _properties.getBorderRoundness()-border), getColor());
    
    xSemaphoreGive(sync_display);
}

ContainerProperties Container::getProperties() {
    return _properties;
}

void Container::setProperties(ContainerProperties properties) {
    _properties = properties;
}

void Container::setBackground(uint16_t color) {
    _properties.setBackgroundColor(color);
    for(Container* content : _content)
        if(content->getProperties().getInvisible())
            content->setBackground(color);
}

uint16_t Container::getColor() {
    return IFNOT(getProperties().getBackgroundColor(), NO_COLOR, ColorManager::getContainerColor(getProperties().getOrder()));
}

void Container::addContent(Container* content, bool atFront) {
    content->setProperties(*content->getProperties().setId(_properties.getNextId()));
    if(!atFront) _content.push_back(content);
    else _content.insert(_content.begin(), content);

    if(!_properties.getDraw())
        return;
    Container::init();
    if(ViewManager::getCurrentView() == _properties.getViewId())
        draw();
}

void Container::removeContent(byte id) {
    Container* content = getContent(id);
    if(content == NULL)
        return;
    content->setProperties(*content->getProperties().setDraw(false));
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
        if(content->getProperties().getId() == id)
            return content;
    return NULL;
}

std::vector<Container*>::iterator Container::getIterator(byte id) {
    if(id > _properties.getCurrentId())
        return _content.end();
    for(auto it = _content.begin(); it != _content.end(); ++it)
        if((*it)->getProperties().getId() == id)
            return it;
    return _content.end();
}