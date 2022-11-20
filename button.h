#include "raylib.h"
class Button{
    public:

    Button(float posX, float posY, float width, float height); //Create button object WITHOUT a texture
    Button(float posX, float posY, float width, float height, char* textureName); //Create button object WITH a texture
    void drawButton(Color userColour); //Draw the button in its specified position
    void drawButton(Color userColour, char* textureName); //Draw the button in its specified position with an updated texture
    void drawLabel(char* text, int fontSize, Color fontColour); //Draws text over the button
    void drawState();
    bool isClicked(Vector2 mousePostion); //Checks if the button was clicked
    //Getters and setters
    void setState(bool newState);
    bool getState();    
    Rectangle getBounds();

    private:
    bool state;
    Rectangle bounds;
    Texture2D texture;
};