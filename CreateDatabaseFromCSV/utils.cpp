# include "utils.h"
#include <algorithm>
#include <iostream>
#include <fstream>

std::string UpperCase(std::string text) {
    //入力された文字列を大文字に変換
    std::transform(text.begin(), text.end(), text.begin(), std::toupper);
    return text;
}

bool CompareString(std::string text1, std::string text2) {
   // return text1 == text2;
    return UpperCase(text1) == UpperCase(text2);
}


std::vector<std::string> Split(std::string* sentence, const char* parse_char, int n) {
    int next_parse_char_index;
    int next_start_index = 0;
    std::vector<std::string> out;

    //whileループではミスで無限ループに陥る可能性があるため
    for (int i = 0; i < n; i++) {
        next_parse_char_index = sentence->find(parse_char, next_start_index);
        if (next_parse_char_index == std::string::npos) {
            out.push_back(sentence->substr(next_start_index, sentence->size()-next_start_index));
            break;
        }

        //分割文字の一つ手前までを出力リストにいれる
        out.push_back(sentence->substr(next_start_index, next_parse_char_index-next_start_index));

        next_start_index = next_parse_char_index + 1;
    }

    return out;
}


std::vector<std::string> read_file(std::string file_name) {
    std::vector<std::string> out;

    if (file_name.empty()) {
        std::cout << "ファイル名が入力されていません" << std::endl;
        return out;
    }

    // 拡張子がないときには、CSV拡張子を追加する
    if (file_name.find(".csv") == std::string::npos) {
        file_name.append(".csv");
    }

    std::ifstream ifs(file_name);

    // ファイルがなかったりして失敗したら終了。
    if (! ifs.is_open()) {
        std::cout << "次のファイルが存在しません [" << file_name << "]" << std::endl;
        return out;
    }

    std::string line;

    // 1行ずつ取り出して、リストに入れていく
    while (! ifs.eof()) {
        std::getline(ifs, line);
        out.push_back(line);
    }

    return out;
}