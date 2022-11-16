#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "raylib.h"
#include <string>

#define MAXCHARS 255

using namespace std;

class TextBox{
    public:
        /**
         * TextBox(x pos, y pos, width, height)
        */
        TextBox(float, float, float, float);

        /**
         * Should be called in the main game loop to update contents. 
         * Captures any keys in ascii range (! to *space*) pressed.
        */
        void captureText();

        /**
         * Return position of textBox.
        */
        Vector2 getPos();

        /**
         * Returns current string stored in text box.
        */
        string getCurrentValue();

        /**
         * Draws box and text to the screen.
        */
        void drawBox();

        /**
         * Should be called when switching states (no longer drawing box).
         * This will reset the textbox's current value.
        */
        void reset();

    
    private:
        Rectangle bounds;
        char currentValue[MAXCHARS+1];
        int fontSize;
        int letterCount;

};


#endif