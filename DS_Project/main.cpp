#include"JSON_File/JsonFile.hpp"
#include"Util/RegexUtil.hpp"
#include"UI/UI.hpp"

int main() {
    // JsonFile json;
    // json.load("json.json");
    // std::ofstream out("jason.json");
    // std::ofstream out1("johnson.json");
    // json.print("", out, true);
    // json.print("", out1, false);
    // UI ui;
    // ui.run();

    JsonFile jsonTest;
    jsonTest.load("test/jsonExample1.json");
    jsonTest.createFromIndex("\"menu\".\"id\".\"some\".\"thing\"");
    std::ofstream out("what.json");
    jsonTest.print("", out, false);

    // std::cout << RegexUtil::valueOfNumericString("4.2e3") << '\n';
    // std::cout << RegexUtil::valueOfNumericString("0") << '\n';
    // std::cout << RegexUtil::valueOfNumericString("-1") << '\n';
    // std::cout << RegexUtil::valueOfNumericString("2.3") << '\n';
    // std::cout << RegexUtil::valueOfNumericString("-33.132") << '\n';

    return 0;
}