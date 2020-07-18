# include "utils.h"
#include <algorithm>
#include <iostream>
#include <fstream>

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


std::vector<std::string> read_file(std::string file_name) {
    std::vector<std::string> out;

    if (file_name.empty()) {
        std::cout << "�t�@�C���������͂���Ă��܂���" << std::endl;
        return out;
    }

    // �g���q���Ȃ��Ƃ��ɂ́ACSV�g���q��ǉ�����
    if (file_name.find(".csv") == std::string::npos) {
        file_name.append(".csv");
    }

    std::ifstream ifs(file_name);

    // �t�@�C�����Ȃ������肵�Ď��s������I���B
    if (! ifs.is_open()) {
        std::cout << "���̃t�@�C�������݂��܂��� [" << file_name << "]" << std::endl;
        return out;
    }

    std::string line;

    // 1�s�����o���āA���X�g�ɓ���Ă���
    while (! ifs.eof()) {
        std::getline(ifs, line);
        out.push_back(line);
    }

    return out;
}