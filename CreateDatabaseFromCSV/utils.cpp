# include "utils.h"

std::string upperCase(std::string text) {
    for (int i = 0; i < text.size(); i++)
        //入力された文字列を大文字に変換
        text[i] = toupper(text[i]);
    return text;
}

bool CompareString(std::string text1, std::string text2) {
    return UpperCase(text1) == UpperCase(text2);
}