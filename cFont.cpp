#include "cFont.h"

const std::string nes_font = "res/nesfont";
const std::string font_file_ext = ".txt";
const int font_size = 16;
const int tile_size = 16;
const int font_height = 128;
const int font_width = 256;
const float letter_width = 16. / float(256);
const float letter_height = 16. / float(128);


cFont::cFont()
{
}


cFont::~cFont()
{
}

void cFont::getCharPosition(char c, float& xo, float& yo, float& xf, float& yf)
{
    xo = positions[c][0];
    yf = positions[c][1];
    xf = xo + letter_width;
    yo = yf + letter_height;
}

int cFont::getFontID() {
    return font_id;
}

void cFont::loadFont()
{
    std::string filename = nes_font + font_file_ext;
    std::ifstream ifs(filename, std::ifstream::binary);
    if (!ifs.good()) {
        throw std::runtime_error("Error loading " + filename);
    }
    std::string s;
    
    ifs >> char_rows;
    ifs >> char_cols;
    std::getline(ifs, s);
    
    for (int i = 0; i < char_rows; ++i) {
        
        std::getline(ifs, s);
        for (int j = 0; j < char_cols; ++j){
            char c;
            c = s[j];
            positions[c][1] = float(i*16)/float(font_height);
            positions[c][0] = float(j*16) / float(font_width);
        }
    }

}
