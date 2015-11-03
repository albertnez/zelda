#include "cAnim.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Frame::TextureOffset(float &xo, float &yo, float &xf, float &yf, int texWidth, int texHeight) {
	xo = float(x) / texWidth;
	yo = float(y + height) / texHeight;
	xf = xo + float(width) / texWidth;
	yf = float(y) / texHeight;
}

cAnim::cAnim() : frame(0), elapsed(0) {
}

Frame cAnim::CurrentFrame() const {
    return frames[frame];
}

void cAnim::InsertFrame(Frame frame) {
    frames.push_back(frame);
}

void cAnim::Advance(int duration) {
    elapsed += duration;
    while (elapsed >= frames[frame].duration) {
        elapsed -= frames[frame].duration;
        frame = (frame + 1) % frames.size();
    }
}

void cAnim::Reset() {
    frame = 0;
    elapsed = 0;
}

int cAnim::Size() const {
    return frames.size();
}

std::unordered_map<std::string, cAnim> LoadAnimations(const std::string &path) {
	std::ifstream ifs(path);
	return ParseAnimations(ifs);
}

std::unordered_map<std::string, cAnim> ParseAnimations(std::ifstream& ifs) {
    static const std::string WHITESPACE{" \t"};  // String with whitespace characters.
    static const std::string COMMENT{"#"};
    static const std::string START{"start"};
    static const std::string END{"end"};

    // State of what we are expecting.
    enum State : int {
        Start = 0,
        Name,
        NumFrames,
        X,
        Y,
        Width,
        Height,
        Duration,
        End,
    };
    int currentState{Start};

    // Magic vector.
    std::vector<int Frame::*> data {
	&Frame::x, &Frame::y, &Frame::width, &Frame::height, &Frame::duration,
    };

    std::string line;
    int numFrames = 0;
    cAnim currentAnim;
    Frame currentFrame;
    std::string animName;

    std::unordered_map<std::string, cAnim> animations;
    while (getline(ifs, line)) {
        // Skip comments.
        line = line.substr(0, line.find_first_of(COMMENT));
        std::istringstream iss(line);
        while (true) {
            std::string token;
            // If no more tokens to read in this line, break;
            if (!(iss >> token)) {
                break;
            }
            if (currentState == Start) {
                if (token != START) {
                    throw std::runtime_error("Error parsing start. Found '" + token + "'");
                }
                ++currentState;
            } else if (currentState == Name) {
                animName = token;
                currentAnim = cAnim();
                ++currentState;
            } else if (currentState == NumFrames) {
                numFrames = std::stoi(token);
                ++currentState;
            } else if (currentState >= X && currentState <= Duration) {
                currentFrame.*data[currentState - State::X] = std::stoi(token);
                if (currentState == Duration) {
                    currentAnim.InsertFrame(currentFrame);
                    if (currentAnim.Size() < numFrames) {
                        currentState = X;
                    } else {
                        ++currentState;
                    }
                } else {
                    ++currentState;
                }
            } else if (currentState == End) {
                if (token != END) {
                    throw std::runtime_error("Error parsing " + token);
                }
                animations[animName] = currentAnim;
                currentState = Start;
            }
        }
    }
    return animations;
}
