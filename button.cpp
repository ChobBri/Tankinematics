#include "button.h"

Button::Button(float posX, float posY, float width, float height){
    bounds = {posX, posY, width, height};
    state = false;
    texture = LoadTexture("resources/noTexture.png");
    hasTexture = false;
}
Button::Button(float posX, float posY, float width, float height, char* textureName){
    bounds = {posX, posY, width, height};
    state = false;
    texture = LoadTexture(textureName);
    hasTexture = true;
}
void Button::drawButton(){
    if (hasTexture)
        DrawTexture(texture, bounds.x, bounds.y, WHITE);
    else
        DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, WHITE);
}
void Button::drawButton(Color userColour){
    if (hasTexture)
        DrawTexture(texture, bounds.x, bounds.y, WHITE);
    else
        DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, userColour);
}
void Button::drawButton(Color userColor, char* textureName){
    texture = LoadTexture(textureName);
    hasTexture = true;
    drawButton(userColor);
}
void Button::drawLabel(char* text, int fontSize, Color fontColour){
    DrawText(text, bounds.x, bounds.y, fontSize, fontColour);
}
bool Button::isClicked(Vector2 mousePosition){
    if(CheckCollisionPointRec(mousePosition, bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return true;
    return false;
}
bool Button::isClicked(){
    if(CheckCollisionPointRec(GetMousePosition(), bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
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