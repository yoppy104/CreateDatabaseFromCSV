# include "utils.h"
#include <algorithm>

std::string UpperCase(std::string text) {
    //���͂��ꂽ�������啶���ɕϊ�
    std::transform(text.begin(), text.end(), text.begin(), std::toupper);
    return text;
}

bool CompareString(std::string text1, std::string text2) {
   // return text1 == text2;
    return UpperCase(text1) == UpperCase(text2);
}