#include <bitset>
#include "base64.h"

const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string BASE64::encode(const unsigned char * t, int len){
    std::string s = "";
    for(int i = 0; i < len ; i++) s +=  std::bitset<8>(t[i]).to_string();
    std::string e = "";
    int length = len*8;
    for(; length % 6 != 0; length++) s += "0";
    for(int i = 0; i < length; i+=6) e += b64[std::stoi(s.substr(i,6), nullptr, 2)];
    for(; length % 24 != 0; length += 6) e += "=";
    return e;
}

std::string BASE64::decode(const unsigned char * t, int len){
    std::string s = "";
    std::string d = "";
    for(int i = 0; i < len ; i++)
        if(strchr(b64,t[i]) != nullptr)
            s += std::bitset<6>(strchr(b64,t[i]) - b64).to_string();
    for(int i = 0; i < s.length(); i += 8) d += char(std::stoi(s.substr(i,8), nullptr, 2));
    return d;
}
