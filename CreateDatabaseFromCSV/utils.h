#pragma once
# include <string>
#include <cctype>
#include <vector>

///<summary>
/// �������啶���ŌŒ肷��
///</summary>
std::string UpperCase(std::string text);

///<summary>
/// ��̕��͗񂪓����������r����
///</summary>
bool CompareString(std::string text1, std::string text2);

///<summary>
/// ���͂��w�蕶���ŕ������Ĕz��Ƃ��ĕԋp����.
///</summary>
std::vector<std::string> Split(std::string* sentence, const char* parse_char, int n = 100);
