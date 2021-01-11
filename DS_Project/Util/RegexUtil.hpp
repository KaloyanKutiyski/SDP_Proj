#pragma once
#include<string>
#include<regex>

namespace RegexUtil {
    //!based off the syntax flowcharts on the official json website
    const std::string JsonString = "\"([^(\\\\)(\\\")[:cntrl:]]|[\\(\\)]|(\\\\)([(\\\\)(\\\")/bfnrt]|u[[:xdigit:]]{4}))*\"";
    const std::string JsonNumber = "-?(0|[1-9](\\d)*)(\\.\\d+)?([Ee][\\+-]?\\d+)?";
    const std::string JsonSpecial = "true|false|null";
    const std::string JsonNonNumericPrimitive = "(" + JsonString + ")|(" + JsonSpecial + ")";

    bool isNonNumericPrimitive(const std::string&);
    bool isKeyNonNumericPrimitive(const std::string&);

    bool isNumericPrimitive(const std::string&);
    bool isKeyNumericPrimitive(const std::string&);
    
    bool isStringPrimitive(const std::string&);

    bool isKeyNewObject(const std::string&);
    bool isKeyNewArray(const std::string&);

    bool isValidCreationKey(const std::string&);
    bool isPositiveInteger(const std::string&);

    bool isOutsideQuotes(const size_t&, const std::string&);
    int findFirstInstanceOfOutsideQuotes(const char&, const std::string&);
    //!splits a string upon a non-quoted ':'
    std::pair<std::string, std::string> splitPair(const std::string&);

    //!splits at the first and last non-quoted dots respectively
    std::pair<std::string, std::string> splitAtFirstDot(const std::string&);
    std::pair<std::string, std::string> splitAtLastDot(const std::string&);

    double valueOfNumericString(const std::string&);
};
 