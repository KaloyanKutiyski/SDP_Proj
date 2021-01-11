#pragma once
#include"RegexUtil.hpp"
#include<assert.h>
#include<cmath>
#include<iostream>

bool RegexUtil::isPrimitive(const std::string& str) {
    std::regex regex(JsonPrimitive);
    return std::regex_match(str, regex);
}
bool RegexUtil::isKeyPrimitive(const std::string& str) {
    std::regex regex(JsonString + ":(" + JsonPrimitive + ")");
    return std::regex_match(str, regex);
}

bool RegexUtil::isKeyNewObject(const std::string& str) {
    std::regex regex(JsonString + ":\\{");
    return std::regex_match(str, regex);
}
bool RegexUtil::isKeyNewArray(const std::string& str) {
    std::regex regex(JsonString + ":\\[");
    return std::regex_match(str, regex);
}


bool RegexUtil::isOutsideQuotes(const size_t& index, const std::string& string) {
    assert(index < string.size());
    unsigned int quoteCount = 0;
    for (int i = 0; i < index; i++) {
        if (string[i] == '\"' && (i == 0 || string[i-1] != '\\')) {
            quoteCount++;
        } 
    }
    return quoteCount % 2 == 0;
}

int RegexUtil::findFirstInstanceOfOutsideQuotes(const char& character, const std::string& string) {
    for (int i = 0; i < string.length(); i++) {
        if (string[i] == character && (i == 0 || string[i-1] != '\\') && isOutsideQuotes(i, string)) {
            return i;
        }
    }
    return -1;
}

std::pair<std::string, std::string> RegexUtil::splitPair(const std::string& string) {
    int index = findFirstInstanceOfOutsideQuotes(':', string);
    std::string key, value;
    if (index != -1) {
        key = string.substr(0, index);
        value = string.substr(index + 1);
    } else {
        key = "";
        value = string;
    }
    if (value.back() == ',') {
        value.pop_back();
    }

    return std::make_pair(key, value);
}

std::pair<std::string, std::string> RegexUtil::splitAtLastDot(const std::string& str) {
    int dotIndex = -1;
    for (int i = str.length() - 1; i >= 0; i--) {
        if (str[i] == '.' && isOutsideQuotes(i, str)) {
            dotIndex = i;
            break;
        }
    }

    std::string left, right;
    if (dotIndex == -1) {
        right = str;
    }
    else { 
        left = str.substr(0, dotIndex);
        right = str.substr(dotIndex + 1);
    }
    return std::make_pair(left, right);
}

double RegexUtil::valueOfNumericString(const std::string& str) {
    double number = 0.0;
    double exponent = 0.0;
    int indexOfExponent = -1;

    if (str.find('e') != std::string::npos) {
        indexOfExponent = str.find('e');
    } else if (str.find('E') != std::string::npos) {
        indexOfExponent = str.find('E');
    }

    if (indexOfExponent == -1) {
        number = std::stod(str);
    } else {
        number = std::stod(str.substr(0, indexOfExponent));
        exponent = std::stod(str.substr(indexOfExponent + 1));
    }

    return number * std::pow(10.0, exponent);
}

bool RegexUtil::isStringPrimitive(const std::string& str) {
    std::regex stringRegex(JsonString);
    return std::regex_match(str, stringRegex);
}

bool RegexUtil::isValidCreationKey(const std::string& str) {
    std::regex regex(JsonString + "(\\." + JsonString + ")*");
    return std::regex_match(str, regex);
}

std::pair<std::string, std::string> RegexUtil::splitAtFirstDot(const std::string& string) {
    int index = findFirstInstanceOfOutsideQuotes('.', string);
    if (index == -1) {
        return std::make_pair(string, "");
    }
    return std::make_pair(string.substr(0, index), string.substr(index + 1));
}

bool RegexUtil::isPositiveInteger(const std::string& str) {
    std::regex reg("0|([1-9]\\d*)");
    return std::regex_match(str, reg);
}
