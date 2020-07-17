# include "utils.h"
#include <algorithm>

std::string UpperCase(std::string text) {
    //入力された文字列を大文字に変換
    std::transform(text.begin(), text.end(), text.begin(), std::toupper);
    return text;
}

bool CompareString(std::string text1, std::string text2) {
   // return text1 == text2;
    return UpperCase(text1) == UpperCase(text2);
}