#pragma once
#include<string>
#include <fstream>





class cFont
{
public:
    cFont();
    ~cFont();
    void getCharPosition(char c, float& xo, float& yo, float& xf, float& yf);
    void loadFont();
    int getFontID();
private:
    float positions[256][2];
    int xPos;
    int yPos;
    int char_rows;
    int char_cols;
    int font_id;

};

