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


std::vector<std::string> Split(std::string* sentence, const char* parse_char, int n) {
    int next_parse_char_index;
    int next_start_index = 0;
    std::vector<std::string> out;

    //while���[�v�ł̓~�X�Ŗ������[�v�Ɋׂ�\�������邽��
    for (int i = 0; i < n; i++) {
        next_parse_char_index = sentence->find(parse_char, next_start_index);
        if (next_parse_char_index == std::string::npos) {
            out.push_back(sentence->substr(next_start_index, sentence->size()-next_start_index));
            break;
        }

        //���������̈��O�܂ł��o�̓��X�g�ɂ����
        out.push_back(sentence->substr(next_start_index, next_parse_char_index-next_start_index));

        next_start_index = next_parse_char_index + 1;
    }

    return out;
}