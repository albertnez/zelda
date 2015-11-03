#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct Frame {
    int x;
    int y;
    int width;
    int height;
    int duration;  // Duration in frames.

    Frame() {}
    // Get the coordinates in texture to draw.
    void TextureOffset(float &xo, float &yo, float &xf, float &yf, int texWidth, int texHeight);
};

class cAnim {
public:
    cAnim();

    Frame CurrentFrame() const;
    void InsertFrame(Frame frame);
    // Advance 'duration' time.
    void Advance(int duration);
    void Reset();
    int Size() const;

private:
    std::vector<Frame> frames;
    int frame;    // Current frame.
    int elapsed;  // Time elapsed on current frame.
};

// Function to parse animations from an std::istream.
std::unordered_map<std::string, cAnim> LoadAnimations(const std::string &path);
std::unordered_map<std::string, cAnim> ParseAnimations(std::ifstream& ifs);

