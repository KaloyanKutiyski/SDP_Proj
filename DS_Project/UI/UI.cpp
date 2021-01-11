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
        } else if (command.empty()) {
            std::cout << '\n';
        } else if (lower(command) == "help") {
            std::cout << helpMessage;
        } else if (lower(splitOff(command, false)) == "load") {
            try {
                splitOff(command, true);
                file.load(command);
                hasFile = true;
                filePath = command;
                std::cout << "file loaded\n";
            } catch (std::invalid_argument e) {
                std::cout << e.what();
            }
        } else if (hasFile) {
            parseCommand(command);
        } else {
            std::cout << "invalid command\n";
        }
    }

    std::cout << endMessage;
}

void UI::parseCommand(std::string& string) {
    std::string command = lower(splitOff(string, true));

    if (command == "save") {
        save(string);
    } else if (command == "savepart") {
        savePart(string);
    } else if (command == "print") {
        print(string);
    } else if (command == "find") {
        find(string);
    } else if (command == "create") {
        create(string);
    } else if (command == "change") {
        change(string);
    } else if (command == "remove") {
        remove(string);
    } else if (command == "move") {
        move(string);
    } else if (command == "sort") {
        sort(string);
    } else if (command == "generate") {
        generate(string);
    }
    else {
        std::cout << "invalid command\n";
    }
}

void UI::save(std::string& string)const {
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
            file.print("", out, mode);
        } catch (std::invalid_argument e) {
            std::cout << e.what();
        }
    } else {
        std::cout << "bad filename\n";
    }
}

void UI::savePart(std::string& string)const {
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

    std::cout << "choose filename\n";
    std::string filename;
    std::getline(std::cin, filename);

    std::ofstream out(filename);
    if (out) {
        try {
            file.print(string, out, mode);
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

void UI::find(std::string& string)const {
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

void UI::create(std::string& str) {
    std::cout << "choose name for the user created object."
                    "Can be left empty if adding to array or primitive."
                    "Can also be used to insert at specific index of array\n";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "write json to console:\n";
    std::string jsonFromConsole;
    std::getline(std::cin, jsonFromConsole);

    try {
        file.attachObjectFromString(jsonFromConsole, str, name);
    } catch (std::invalid_argument e) {
        std::cout << e.what();
    }
}

void UI::change(std::string& str) {
    std::cout << "write json input to console:\n";
    std::string jsonFromConsole;
    std::getline(std::cin, jsonFromConsole);
    try {
        file.changeElement(str, jsonFromConsole);
    } catch (std::invalid_argument e) {
        std::cout << e.what();
    }
}

void UI::remove(std::string& str) {
    try {
        file.removeElement(str, true);
    } catch (std::invalid_argument e) {
        std::cout << e.what();
    }
}

void UI::move(std::string& str) {
    std::cout << "choose name for the moved element\n";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "move to\n";
    std::string place;
    std::getline(std::cin, place);

    try {
        file.moveElement(str, place, name);
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

void UI::generate(std::string& str) {
    try {
        file.createFromIndex(str);
    } catch (std::invalid_argument e) {
        std::cout << e.what();
    }
}

const std::string UI::beginMessage =
    "welcome to my json parser. enter 'help' for an overview of user commands\n"
    "keep in mind that until a file is loaded, the only commands avaliable are 'help', 'load' and 'quit'\n";
const std::string UI::endMessage = 
    "shutting down\n";
const std::string UI::helpMessage = 
    "overview of commands:\n"
    "quit\n"
    "\tquits the program\n"
    "save <normal/concise> <filename>\n"
    "\tsaves the file with the chosen format. leave the filename empty to save to current file\n"
    "savepart <normal/concise> <key>\n"
    "\tgives a prompt to choose a filename. saves the selected part in the selected format\n"
    "print <normal/concise> <key>\n"
    "\tprints the selected part in the selected format to the console\n"
    "find <number/all> <name>\n"
    "\tfinds either all or the nth instance of an element with that name\n"
    "change <key>\n"
    "\tgives a prompts to input json from the console. parses the json and replaces the element with it\n"
    "create <key>\n"
    "\tgives a prompts to input json from the console. parses the json and adds a subelement to the selected element\n"
    "remove <key>\n"
    "\tremoves the selected element\n"
    "move <key>\n"
    "\tchoose an element to be moved. gives a prompt for a name and a destination\n"
    "sort <key>\n"
    "\tif the selected element is a sortable array it is sorted\n"
    "generate <key>\n"
    "\tadds a json structure to the file based on the given key\n";


