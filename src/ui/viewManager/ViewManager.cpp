/*
 ViewManager.cpp - ViewManager-Library for Librarys.
*/

#include "ViewManager.h"

std::vector<View*> ViewManager::views;
short ViewManager::currentView = 0;

void ViewManager::addView(View* view) {
  views.push_back(view);
  // view->init();
}

void ViewManager::init() {
  for(View* view : views) {
    view->init();
  }
  setCurrentView(DEFAULT_VIEW);
}

void ViewManager::setCurrentView(short view) {
  if(!VALID_VIEW(view))
    return;
  currentView = view;
  getView(view)->draw();
}

short ViewManager::getCurrentView() {
  return currentView;
}

View* ViewManager::getView(short view) {
  if(!VALID_VIEW(view))
    return NULL;
  return views[view];
}

std::vector<View*> ViewManager::getViews() {
  return views;
}