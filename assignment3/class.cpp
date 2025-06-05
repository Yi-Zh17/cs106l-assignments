#include "class.h"

Rectangle::Rectangle(double width, double height) {
    this->width = width;
    this->height = height;
    updateSize();
}

Rectangle::Rectangle() {
    this->width = 2.0;
    this->height = 1.0;
    updateSize();
}

double Rectangle::getWidth() const {
    return this->width;
}

double Rectangle::getHeight() const {
    return this->height;
}

double Rectangle::getSize() const {
    return this->size;
}

void Rectangle::setWidth(double newWidth) {
    this->width = newWidth;
}

void Rectangle::setHeight(double newHeight) {
    this->height = newHeight;
}

void Rectangle::updateSize() {
    this->size = calcSize(this->width, this->height);
}

double Rectangle::calcSize(double width, double height) {
    return width * height;
}
