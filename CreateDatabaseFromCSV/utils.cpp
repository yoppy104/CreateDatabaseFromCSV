# include "utils.h"

std::string upperCase(std::string text) {
    for (int i = 0; i < text.size(); i++)
        //“ü—Í‚³‚ê‚½•¶Žš—ñ‚ð‘å•¶Žš‚É•ÏŠ·
        text[i] = toupper(text[i]);
    return text;
}

bool CompareString(std::string text1, std::string text2) {
    return UpperCase(text1) == UpperCase(text2);
}