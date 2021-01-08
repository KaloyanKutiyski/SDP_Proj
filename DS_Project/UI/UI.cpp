#pragma once
#include"UI.hpp"
#include<iostream>
#include<cstring>
#include"../Util/RegexUtil.hpp"

UI::UI(): hasFile{false} {
}

void UI::trim(std::string& string)const {
    while(!string.empty() && isspace(string.front())) {
        string = string.substr(1);
    }
    while(!string.empty() && isspace(string.back())) {
        string.pop_back();
    }
}

std::string UI::lower(const std::string& string)const {
    std::string res;
    for (char c : string) {
        res.push_back(tolower(c));
    }
    return res;
}

std::string UI::splitOff(std::string& string, const bool& removalMode)const {
    trim(string);
    std::string res;
    size_t index = string.find(' ');
    if (index == std::string::npos) {
        res = string;
        if (removalMode) {
            string.clear();
        }
    } else {
        res = string.substr(0, index);
        if (removalMode) {
            string = string.substr(index + 1);
            trim(string);
        }
    }
    return res;
}

bool UI::isAllNum(const std::string& str)const {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}



void UI::run() {
    std::cout << beginMessage;

    while (true) {
        std::string command;
        std::getline(std::cin, command);
        trim(command);

        if (lower(command) == "quit") {
            break;
        } else if (lower(command) == "help") {
            std::cout << helpMessage;
        } else if (lower(splitOff(command, false)) == "load") {
            try {
                splitOff(command, true);
                file.load(command);
                hasFile = true;
                filePath = command;
            } catch (std::invalid_argument e) {
                std::cout << e.what();
            }
        } else if (hasFile) {
            parseCommand(command);
        } else {
            std::cout << errorMessage;
        }
    }

    std::cout << endMessage;
}

void UI::parseCommand(std::string& string) {
    std::string command = lower(splitOff(string, true));

    if (command == "save") {
        save(string);
    } else if (command == "print") {
        print(string);
    } else if (command == "search") {
        keySearch(string);
    } else if (command == "attach") {
        attachElement(string);
    } else if (command == "change") {
        changeElement(string);
    } else if (command == "remove") {
        deleteElement(string);
    } else if (command == "move") {
        moveElement(string);
    } else if (command == "sort") {
        sort(string);
    } else {
        std::cout << errorMessage;
    }
}

void UI::save(std::string& string)const {
    std::cout << "choose path to a subobject. leave empty to save the entire file\n";
    std::string part;
    std::getline(std::cin, part);

    std::string modeWord = lower(splitOff(string, true));
    bool mode;
    if (modeWord == "normal") {
        mode = false;
    } else if (modeWord == "concise") {
        mode = true;
    } else {
        std::cout << "mode of saving could not be determined\n";
        return;
    }

    std::ofstream out;
    if (string.empty()) {
        out.open(filePath);
    } else {
        out.open(string);
    }
    if (out) {
        try {
            file.print(part, out, mode);
        } catch (std::invalid_argument e) {
            std::cout << e.what();
        }
    } else {
        std::cout << "bad filename\n";
    }
}

void UI::print(std::string& string)const {
    std::string modeWord = lower(splitOff(string, true));
    bool mode;
    if (modeWord == "normal") {
        mode = false;
    } else if (modeWord == "concise") {
        mode = true;
    } else {
        std::cout << "mode of saving could not be determined\n";
        return;
    }

    try {
        file.print(string, std::cout, mode);
    } catch (std::invalid_argument e) {
        std::cout << e.what();
    }
}

void UI::keySearch(std::string& string)const {
    std::cout << "choose file destination, leave empty to print to console\n";
    std::string destination;
    std::getline(std::cin, destination);

    std::string elemChoice = splitOff(string, true);
    if (lower(elemChoice) == "all") {
        file.getAllByKey(string, destination);
    } else if (isAllNum(elemChoice)) {
        try {
            file.getNthByKey(string, std::stoi(elemChoice), destination);
        } catch (std::out_of_range e) {
            std::cout << e.what();
        }
    }
}

void UI::attachElement(std::string& str) {
    std::cout << "choose name for the user created object. Can be left empty if adding to array";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "write json input to console:\n";
    std::string jsonFromConsole;
    std::getline(std::cin, jsonFromConsole);

    try {
        file.attachObjectFromString(jsonFromConsole, str, name);
    } catch (std::invalid_argument e) {
        std::cout << e.what();
    }
}

void UI::changeElement(std::string& str) {
    std::cout << "write json input to console:\n";
    std::string jsonFromConsole;
    std::getline(std::cin, jsonFromConsole);
    try {
        file.changeElement(str, jsonFromConsole);
    } catch (std::invalid_argument e) {
        std::cout << e.what();
    }
}

void UI::deleteElement(std::string& str) {
    try {
        file.removeElement(str, true);
    } catch (std::invalid_argument e) {
        std::cout << e.what();
    }
}

void UI::moveElement(std::string& str) {
    std::cout << "move to\n";
    std::string place;
    std::getline(std::cin, place);

    try {
        file.moveElement(str, place);
    } catch (std::invalid_argument e) {
        std::cout << e.what();
    }
}

void UI::sort(std::string& str) {
    try {
        file.sortArray(str);
    } catch (std::invalid_argument e) {
        std::cout << e.what();
    }
}