#ifndef base64_h
#define base64_h

#include <string>

class BASE64 {
public:
    static std::string encode(const unsigned char * t, int len);
    static std::string decode(const unsigned char * t, int len);
};

#endif
