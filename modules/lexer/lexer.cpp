#include "lexer.h"

token_type getToken(const std::string& word) {
    if(word == "_" || word == "a" ||  word == "b" ||  word == "c" ||  word == "d" ||  word == "e" ||  word == "f" ||  word == "g" ||
    word == "h" ||  word == "i" ||  word == "j" ||  word == "k" ||  word == "l" ||  word == "m" ||  word == "n" ||
    word == "o" ||  word == "p" ||  word == "q" ||  word == "r" ||  word == "s" ||  word == "t" ||  word == "u" ||
    word == "v" ||  word == "w" ||  word == "x" ||  word == "y" ||  word == "z" ||  word == "A" ||  word == "B" ||
    word == "C" ||  word == "D" ||  word == "E" ||  word == "F" ||  word == "G" ||  word == "H" ||  word == "I" ||
    word == "J" ||  word == "K" ||  word == "L" ||  word == "M" ||  word == "N" ||  word == "O" ||  word == "P" ||
    word == "Q" ||  word == "R" ||  word == "S" ||  word == "T" ||  word == "U" ||  word == "V" ||  word == "W" ||
    word == "X" ||  word == "Y" ||  word == "Z"){
        return token_identifier;
    }
    if(word == "0" || word == "1" ||  word == "2" ||  word == "3" ||  word == "4" ||  word == "5" ||  word == "6" ||  word == "7"||
    word == "8" ||  word == "9"){
        return token_int;
    }


    return token_string;
}


std::string get_file_contents(const char *filename)
{
    std::FILE *fp = std::fopen(filename, "rb");
    if (fp)
    {
        std::string contents;
        std::fseek(fp, 0, SEEK_END);
        contents.resize(std::ftell(fp));
        std::rewind(fp);
        std::fread(&contents[0], 1, contents.size(), fp);
        std::fclose(fp);
        return(contents);
    }
    return "INVALID FILE";
}

void parseIdentifier(const std::string& content, int& current_index, std::vector<token>& tokens_vector){
    #define c content[current_index]
    std::string word;

    if(std::isalpha(c)){
        while(std::isalnum(c)){
            word += c;
            current_index++;
        }
        if(!word.empty()){
            if(word == "auto" || word == "break" || word == "case" || word == "char" || word == "const" ||
               word == "continue" || word == "default" || word == "do" || word == "double" || word == "else" ||
               word == "enum" || word == "extern" || word == "float" || word == "for" || word == "goto" ||
               word == "if" || word == "inline" || word == "int" || word == "long" || word == "register" ||
               word == "restrict" || word == "return" || word == "short" || word == "signed" || word == "sizeof" ||
               word == "static" || word == "string" ||  word == "struct" || word == "switch" || word == "typedef" ||
               word == "union" || word == "unsigned" || word == "void" || word == "volatile" || word == "while" ||
               word == "_Alignas" || word == "_Alignof" || word == "_Atomic" || word == "_Bool" || word == "_Complex" ||
               word == "_Generic" || word == "_Imaginary" || word == "_Noreturn" || word == "_Static_assert" ||
               word == "_Thread_local")
            {
                tokens_vector.push_back({word,token_keyword});
                return;
            }
            tokens_vector.push_back({word,token_identifier});
            return;
        }
    }

    if(c == '-'){
        current_index++;
        if(std::isdigit(c)){
            current_index--;
            word += c;
            current_index++;
        } else{
            current_index--;
        }
    }

    if(std::isdigit(c)){
        while(std::isdigit(c)){
            word += c;
            current_index++;
        }
        if(c == '.'){
            word += c;
            current_index++;
            while(std::isdigit(c)){
                word += c;
                current_index++;
            }
            if(!word.empty()){
                tokens_vector.push_back({word,token_float});
                return;
            }
        }
        if(!word.empty()){
            tokens_vector.push_back({word,token_int});
            return;
        }

    }


    #undef c
}

void parseString(const std::string& content, int& current_index, std::vector<token>& tokens_vector){
#define c content[current_index]
    std::string str;
    current_index++;
    while(c != '\"'){
        str += c;
        current_index++;
    }
    //std::cout << "\"" << str << "\"" << std::endl;
    tokens_vector.push_back({str,token_string});
#undef c
}

void parseFile(const char* filepath, std::vector<token> tokens_vector) {
    std::string content = get_file_contents(filepath);

    for(int i = 0; i < content.length(); i++)
    {
        #define c content[i]
        if(c == ' ' || c == '\n' || c == '\t'){
            continue;
        }


        parseIdentifier(content, i, tokens_vector);

        switch(c){
            case '(':
                tokens_vector.push_back({"(",token_open_parenthesis});
                break;
            case ')':
                tokens_vector.push_back({")",token_close_parenthesis});
                break;
            case '{':
                tokens_vector.push_back({"{",token_open_brace});
                break;
            case '}':
                tokens_vector.push_back({"}",token_close_brace});
                break;

            case '+':
                tokens_vector.push_back({"+",token_addition_operator});
                break;
            case '-':
                tokens_vector.push_back({"-",token_subtraction_operator});
                break;
            case '/':
                i++;
                if (c == '/'){
                    tokens_vector.push_back({"//",token_floored_division_operator});
                } else {
                    tokens_vector.push_back({"/",token_division_operator});
                    i--;
                }
                break;
            case '*':
                tokens_vector.push_back({"*",token_multiplication_operator});
                break;
            case '%':
                tokens_vector.push_back({"%",token_modulus_operator});
                break;

            case '=':
                tokens_vector.push_back({"=",token_equal_sign});
                break;
            case ';':
                tokens_vector.push_back({";",token_semi_colon});
                break;
            case '\"':
                parseString(content, i, tokens_vector);
                break;
        }
        #undef c
    }
    for(const token& tok:tokens_vector)
        std::cout << getTokenName(tok.type) << ": " << tok.word << "\n";
}

std::string getTokenName(unsigned int type_num) {
    switch(type_num){
        case token_keyword:                   return "         keyword";
        case token_identifier:                return "      identifier";
        case token_int:                       return "             int";
        case token_float:                     return "           float";
        case token_string:                    return "          string";

        case token_addition_operator:         return "        addition";
        case token_subtraction_operator:      return "     subtraction";
        case token_division_operator:         return "        division";
        case token_multiplication_operator:   return "  multiplication";
        case token_floored_division_operator: return "floored-division";
        case token_modulus_operator:          return "         modulus";

        case token_open_parenthesis:          return "         L-paren";
        case token_close_parenthesis:         return "         R-paren";
        case token_open_brace:                return "         L-brace";
        case token_close_brace:               return "         R-brace";
        case token_equal_sign:                return "          equals";
        case token_semi_colon:                return "      semi-colon";
        default:
            return "??????";
    }
}
