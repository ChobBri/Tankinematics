#include "button.h"

Button::Button(float posX, float posY, float width, float height){
    bounds = {posX, posY, width, height};
    state = false;
}
Button::Button(float posX, float posY, float height, float width, char* textureName){
    bounds = {posX, posY, width, height};
    texture = LoadTexture(textureName);
    state = false;
}
void Button::drawButton(Color userColour){
    DrawRectangleRec(bounds, userColour);
}
void Button::drawButton(Color userColor, char* textureName){
    texture = LoadTexture(textureName);
    drawButton(userColor);
}
void Button::drawLabel(char* text, int fontSize, Color fontColour){
    DrawText(text, bounds.x, bounds.y, fontSize, fontColour);
}
void Button::drawState() {
    if (state) {
        drawButton(GREEN);
    }
    else {
        drawButton(RED);
    }
}
bool Button::isClicked(Vector2 mousePosition){
    if(CheckCollisionPointRec(mousePosition, bounds))
        return true;
    return false;
}
void Button::setState(bool newState){
    this->state = newState;
}
bool Button::getState(){
    return this->state;
}
Rectangle Button::getBounds(){
    return this->bounds;
}