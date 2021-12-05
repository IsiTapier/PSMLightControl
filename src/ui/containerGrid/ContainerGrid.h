/*
  ContainerGrid.h - ContainerGrid-Library for Airduino.
*/

#ifndef ContainerGrid_h
#define ContainerGrid_h

#include "Arduino.h"
#include "../container/Container.h"

class ContainerGrid : public Container {
  public:
    ContainerGrid(ContainerProperties properties, ContainerProperties contentProperties, bool autoSize, std::vector<Container*> content);

    void init() override;

  private:
    ContainerProperties _contentProperties;
    bool _autoSize;

};

#endif
