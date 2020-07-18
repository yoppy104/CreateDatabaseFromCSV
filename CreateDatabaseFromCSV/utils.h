#pragma once
# include <string>
#include <cctype>
#include <vector>

///<summary>
/// •¶š—ñ‚ğ‘å•¶š‚ÅŒÅ’è‚·‚é
///</summary>
std::string UpperCase(std::string text);

///<summary>
/// “ñ‚Â‚Ì•¶Í—ñ‚ª“™‚µ‚¢‚©‚ğ”äŠr‚·‚é
///</summary>
bool CompareString(std::string text1, std::string text2);

///<summary>
/// •¶Í‚ğw’è•¶š‚Å•ªŠ„‚µ‚Ä”z—ñ‚Æ‚µ‚Ä•Ô‹p‚·‚é.
///</summary>
std::vector<std::string> Split(std::string* sentence, const char* parse_char, int n = 100);
