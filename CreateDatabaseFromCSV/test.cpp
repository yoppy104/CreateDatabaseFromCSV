#include "test.h"

#include <iostream>
#include <string>
#include <vector>

#include "utils.h"



void split_test() {
    std::string sentence = "a,c,d,e,vt,aaaa,1234,";

    std::vector<std::string> data = Split(&sentence, ",");

    std::cout << "input_sentence : " << sentence << std::endl;

    for (auto itr = data.begin(); itr != data.end(); itr++) {
        std::cout << *itr << std::endl;
    }
}