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


std::vector<std::string> Split(std::string sentence, const char* parse_char, int n) {
    int next_parse_char_index;
    std::vector<std::string> out = std::vector<std::string>();

    //whileループではミスで無限ループに陥る可能性があるため
    for (int i = 0; i < n; i++) {
        next_parse_char_index = sentence.find(parse_char);
        if (next_parse_char_index == std::string::npos) {
            out.push_back(sentence);
            break;
        }

        //分割文字の一つ手前までを出力リストにいれる
        out.push_back(sentence.substr(0, next_parse_char_index));

        //そこまでの文章を削除
        sentence.erase(0, next_parse_char_index+1);
    }

    return out;
}