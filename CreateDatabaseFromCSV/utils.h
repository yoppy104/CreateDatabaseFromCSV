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

///<summary>
/// �t�@�C�����̕��͂�vector<string>�̌`���ŕԂ�
///</summary>
std::vector<std::string> read_file(std::string file_name);


/// <summary>
/// DB�\���R�[���o�b�N����
/// </summary>
/// <param name="user_data"></param>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <param name="field"></param>
/// <returns></returns>
int show(void*, int, char**, char**);
