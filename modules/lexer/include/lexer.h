#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

enum token_type{
    token_keyword,

    token_identifier,
    token_int,
    token_float,
    token_string,

    token_open_parenthesis,
    token_close_parenthesis,
    token_open_brace,
    token_close_brace,
    token_addition_operator,
    token_subtraction_operator,
    token_division_operator,
    token_multiplication_operator,
    token_floored_division_operator,
    token_modulus_operator,
    token_equal_sign,
    token_semi_colon,
};

std::string getTokenName(unsigned int type_num);

struct token{
    std::string word;
    token_type type;
};

void parseFile(const char* filepath, std::vector<token> tokens_vector);
token_type getToken(const std::string& word);