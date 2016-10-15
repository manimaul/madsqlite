//
// Created by William Kamp on 10/15/16.
//

#include <string>

static std::string upperCaseString(char const *str) {
    std::string aStr(str);
    std::transform(aStr.begin(), aStr.end(), aStr.begin(), ::toupper);
    return aStr;
}

static std::string lowerCaseString(char const *str) {
    std::string aStr(str);
    std::transform(aStr.begin(), aStr.end(), aStr.begin(), ::tolower);
    return aStr;
}

static std::string upperCaseString(std::string const &str) {
    return upperCaseString(str.c_str());
}

static std::string lowerCaseString(std::string const &str) {
    return lowerCaseString(str.c_str());
}