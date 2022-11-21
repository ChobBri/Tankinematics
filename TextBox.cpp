#include "TextBox.hpp"
#include <iostream>

using namespace std;

TextBox::TextBox(float x, float y, float width, float height){
    bounds = Rectangle{x, y, width, height};
    currentValue[0] = '\0';
    fontSize = width/14;
    letterCount = 0;
}

void TextBox::captureText(){
    // Get char pressed (unicode character) on the queue
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0)
    {
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (letterCount < MAXCHARS) && MeasureText(currentValue, fontSize) < (bounds.width - fontSize)) //is a valid char, under char limit AND within box width
        {
            cout << "measureText: " << MeasureText(currentValue, fontSize) << endl;
            currentValue[letterCount] = (char)key;
            currentValue[letterCount+1] = '\0'; // Add null terminator at the end of the string.
            letterCount++;
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        currentValue[letterCount] = '\0';
    }
}

Vector2 TextBox::getPos(){
    return Vector2{bounds.x, bounds.y};
}

string TextBox::getCurrentValue(){
    return currentValue;
}

void TextBox::drawBox(){
    DrawRectangleRec(bounds, LIGHTGRAY);
    DrawText(currentValue, bounds.x, bounds.y, fontSize, BLACK);
}

void TextBox::reset(){
    for (char& i : currentValue){
        if (i != '\0')
            i = '\0';
    }
    letterCount = 0;
    return;
}
        