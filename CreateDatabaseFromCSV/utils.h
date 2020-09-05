#pragma once
# include <string>
#include <cctype>
#include <vector>

///<summary>
/// 文字列を大文字で固定する
///</summary>
std::string UpperCase(std::string text);

///<summary>
/// 二つの文章列が等しいかを比較する
///</summary>
bool CompareString(std::string text1, std::string text2);

///<summary>
/// 文章を指定文字で分割して配列として返却する.
///</summary>
std::vector<std::string> Split(std::string* sentence, const char* parse_char, int n = 100);

///<summary>
/// ファイル内の文章をvector<string>の形式で返す
///</summary>
std::vector<std::string> read_file(std::string file_name);


/// <summary>
/// DB表示コールバック処理
/// </summary>
/// <param name="user_data"></param>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <param name="field"></param>
/// <returns></returns>
int show(void*, int, char**, char**);
