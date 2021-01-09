#pragma once
#include"JsonFile.hpp"
#include"../Object/object.hpp"
#include"../Object/Composite/composite.hpp"
#include"../Object/ObjectArray/objectArray.hpp"
#include"../Object/Primitive/primitive.hpp"
#include"../Util/RegexUtil.hpp"
#include<stack>
#include<fstream>

void JsonFile::addToBucket(std::string& bucket, const char& curr, bool& isEscaped, bool& inQuotes) {
    bucket += curr;
    if (curr == '\\' && !isEscaped) {
        isEscaped = true;
    } else {
        if (curr == '\"' && !isEscaped) {
            inQuotes = !inQuotes;
        }
        isEscaped = false;
    }
}

void JsonFile::tryToCreateNewObject(std::string& bucket, std::stack<Object*>& objectStack) {
    Object* newObj = nullptr;
    std::pair<std::string, std::string> bucketPair = RegexUtil::splitPair(bucket);
            
    if (objectStack.top()->getType() == COMPOSITE) {
        if (RegexUtil::isKeyNewObject(bucket)) {
            newObj = new Composite();
        } else if (RegexUtil::isKeyNewArray(bucket)) {
            newObj = new ObjectArray();
        } else if (RegexUtil::isKeyNonNumericPrimitive(bucket)) {
            newObj = new Primitive(bucketPair.second);
        }
            
    } else if (objectStack.top()->getType() == ARRAY) {
        if (bucket == "{") {
            newObj = new Composite();
        } else if (bucket == "[") {
            newObj = new ObjectArray();
        } else if (RegexUtil::isNonNumericPrimitive(bucket)) {
            newObj = new Primitive(bucket);
        }
    }

    if (newObj) {
        objectStack.top()->addChild(bucketPair.first, newObj);
        if (newObj->getType() != PRIMITIVE) {
            objectStack.push(newObj);
        }
        bucket.clear();
    }
}

Object* JsonFile::parse(std::istream& in) {
    std::string bucket;
    std::stack<Object*> objectStack;
    
    Object* res = nullptr;
    char curr;
    in.read(&curr, 1);
    if (curr == '{') {
        res = new Composite();
    } else if (curr == '[') {
        res = new ObjectArray();
    } else { 
        /// this case handles creation of primitives.
        /// early return as the rest of the logic only has meaning
        /// if the object is not primitive
        std::string content;
        char c;
        while (in.read(&c, 1)) {
            content += c;
        }
        
        if (RegexUtil::isNonNumericPrimitive(content) || RegexUtil::isNumericPrimitive(content)) {
            res = new Primitive(content); 
        }
        
        return res;
    }

    objectStack.push(res);

    bool inQuotes = false;
    bool isEscaped = false;
     
    while(in.read(&curr, 1)) {

        if (!inQuotes && !bucket.empty() && (curr == '}' || curr == ']' || curr == ',')) {
            
            /// since often the prefix of a valid number is another valid number
            /// we cannot simply stop reading after finding the shortest string
            /// containing a valid number, instead we only stop reading
            /// when met with a next object ( signified by ',' ) or end of object ( '}' or ']' ) 
            if (objectStack.top()->getType() == COMPOSITE && RegexUtil::isKeyNumericPrimitive(bucket)) {
                std::pair<std::string, std::string> bucketAsPair = RegexUtil::splitPair(bucket);
                objectStack.top()->addChild(bucketAsPair.first, new Primitive(bucketAsPair.second));
            } else if (objectStack.top()->getType() == ARRAY && RegexUtil::isNumericPrimitive(bucket)) {
                objectStack.top()->addChild("", new Primitive(bucket));
            } else {
                /// failstate:
                /// we have reached a ',' meaning next object expected or ']' or '}' meaning end of object
                /// yet the data before that could not be parsed
                root->destroy();
                delete root;
                return nullptr;
            }
            
            if (curr == '}' || curr ==']') {
                bucket = curr;
            } else {
                bucket.clear();
            }
        
        /// characters which do not carry any meaning and can be discarded
        /// doing so simplifies the recognision of objects
        /// as there is no need to check for and remove meaningless leading symbols
        } else if (!inQuotes && (curr == ' ' 
                                    || curr == '\n'
                                    || curr == '\r'
                                    || curr == '\v'
                                    || curr == '\f'
                                    || curr == '\t')
                    || bucket.empty() && curr == ',') {
            continue;
        } else {
            /// used to reduce indentation levels
            addToBucket(bucket, curr, isEscaped, inQuotes);
        }      

        if (bucket == "}" || bucket == "]") {

            objectStack.pop();
            bucket.clear();
        } else {
            tryToCreateNewObject(bucket, objectStack);
        }
    }
    return res;
}

void JsonFile::load(const std::string& filePath) {
    std::ifstream in(filePath);
    if (!in || !in.good()) {
        throw std::invalid_argument("bad file\n");
    }
    if (!(fileIsBalanced(filePath))) {
        throw std::invalid_argument("unbalanced file\n");
    }
    Object* temp = parse(in);
    if (temp) {
        root = temp;
    } else {
        throw std::invalid_argument("file does not match json file\n");
    }
}

bool JsonFile::sourceIsBalanced(std::istream& in)const {
    std::stack<char> parentheses;
    bool inQuotes = false;
    bool isEscaped = false;
    char curr; 
    while(in.read(&curr, 1)) {        
        if (curr == '\"' && !isEscaped) {
            inQuotes = !inQuotes;
        } else if (!inQuotes && (curr == '{' || curr == '[')) {
            parentheses.push(curr);
        } else if (!inQuotes && curr == '}') {
            if (parentheses.empty() || parentheses.top() != '{') {
                return false;
            }
            parentheses.pop();
        } else if (!inQuotes && curr == ']') {
            if (parentheses.empty() || parentheses.top() != '[') {
                return false;
            }
            parentheses.pop();
        }

        /// a bit of hack but reduces indentation levels
        /// is not an else if because setting isEscaped to false is needed in all other cases
        if (curr == '\\' && !isEscaped) {
            isEscaped = true;
        } else {
            isEscaped = false;
        }
    }
    return !isEscaped && !inQuotes && parentheses.empty();
}

bool JsonFile::stringIsBalanced(const std::string& str)const {
    std::stringstream ss(str);
    return sourceIsBalanced(ss);
}

bool JsonFile::fileIsBalanced(const std::string& string)const {
    std::ifstream in(string);
    if (!in || !in.good()) {
        return false;
    }
    return sourceIsBalanced(in);
}

void JsonFile::print(Object* rootObj, std::ostream& out, const bool& concise)const {
    if (rootObj->getType() == PRIMITIVE) {
        out << rootObj->toString();
        return;
    }

    std::stack<std::pair<std::pair<std::string, Object*>, int>> printStack;
    printStack.push(std::make_pair(std::make_pair("", rootObj), 0));
    
    out << rootObj->opener();
    if (!concise && rootObj->getType() != PRIMITIVE) {
        out << '\n';
    }
    while (!printStack.empty()) {
        Object* currObj = printStack.top().first.second;
        int currIndex = printStack.top().second;
        std::pair<std::string, Object*> next = currObj->getNth(currIndex);


        if (next.first == "" && next.second == nullptr) {
            out << currObj->closer();
            printStack.pop();
            if (!printStack.empty()) {
                printStack.top().second++;
            }

        } else {
            if (currIndex != 0) {
                out << ',' << (concise ? "\n" : "");
            }
            if (!concise) {
                printNTabs(printStack.size(), out);
            }

            if (next.second->getType() == PRIMITIVE) {
                out << next.first << next.second->toString();
                printStack.top().second++;

            } else {
                out << next.first << next.second->opener();
                printStack.push(std::make_pair(next, 0));
            }
        }
    }
    std::cout << '\n';
}

void JsonFile::printNTabs(const size_t& n, std::ostream& out)const {
    for (int i = 0; i < n; i++) {
        out << '\t';
    }
}


void JsonFile::print(const std::string& object, std::ostream& out, const bool& concise)const {
    Object* subObject = get(object);
    if (subObject) {
        print(subObject, out, concise);
    } else {
        throw std::invalid_argument("no object exists at this path");
    }
}

void JsonFile::print(const std::string& object, const bool& concise)const {
    print(object, std::cout, concise);
}

void JsonFile::print(const std::string& object, std::string& output, const bool& conscise)const {
    std::stringstream ss;
    print(get(object), ss, conscise);
    while(ss) {
        ss >> output;
    }
}


JsonFile::JsonFile(): root{nullptr} {
}
JsonFile::~JsonFile() {
    if (root) {
        root->destroy();
        delete root;
    }
}

Object* JsonFile::get(const std::string& query)const {
    return get(root, query);
}

Object* JsonFile::get(Object* obj, const std::string& query)const {
    if (query.empty()) {
        return obj;
    }
    if (query.find('.') == std::string::npos) {
        return obj->get(query);
    } else {
        int splitIndex = query.find('.');
        return get(obj->get(query.substr(0, splitIndex)), (query.substr(splitIndex + 1)));
    }
    return nullptr;
}

void JsonFile::upliftPrimitive(Object* destination, const std::string& dest) {
    std::string oldVal = destination->toString();
    std::pair<std::string, std::string> destinationAndParent = RegexUtil::splitAtLastDot(dest);
    removeElement(dest, true);
    Object* parent = get(destinationAndParent.first);
    destination = new ObjectArray();
    parent->addChild(destinationAndParent.second, destination);
    destination->addChild("", new Primitive(oldVal));
}

void JsonFile::attachObjectFromString(const std::string& src, const std::string& dest, const std::string& name) {
    Object* parent = get(dest);
    if (!parent) {
        throw std::invalid_argument("no such element in json file\n");
    }
    if (!stringIsBalanced(src)) {
        throw std::invalid_argument("source is unbalanced\n");
    }

    std::stringstream objString(src);
    Object* parsed = parse(objString);
    if (!parsed) {
        throw std::invalid_argument("invalid json string\n");
    }

    if (parent->getType() == PRIMITIVE) {
        upliftPrimitive(parent, dest);
    }
    if (parent->getType() == COMPOSITE && !RegexUtil::isStringPrimitive(name)) {
        throw std::invalid_argument("name is not a valid json string\n");
    }
    parent->addChild(name, parse(objString));
}

void JsonFile::changeElement(const std::string& dest, const std::string& src) {
    if (!stringIsBalanced(src)) {
        throw std::invalid_argument("unbalanced source\n");
    }
    if (!get(dest)) {
        throw std::invalid_argument("no such element\n");
    }

    Object* toAdd;
    std::stringstream sourceStream(src);
    toAdd = parse(sourceStream);
    
    if (!toAdd) {
        throw std::invalid_argument("invalid json input\n");
    }

    if (dest.empty()) {
        root->destroy();
        delete root;
        std::stringstream sourceStream(src);
        root = toAdd;
        return;
    }

    removeElement(dest, true);
    std::pair<std::string, std::string> beforeAndAfterDot = RegexUtil::splitAtLastDot(dest);
    get(beforeAndAfterDot.first)->addChild(beforeAndAfterDot.second, toAdd);
}

void JsonFile::removeElement(const std::string& str, const bool& destroyMode) {
    std::pair<std::string, std::string> getPartAndRemovePart = RegexUtil::splitAtLastDot(str);

    if (str.empty()) {
        root->destroy();
        delete root;
    }
    else if (get(str)) {
        get(getPartAndRemovePart.first)->remove(getPartAndRemovePart.second, destroyMode);
    } else {
        throw new std::invalid_argument("no such element\n");
    }
}

void JsonFile::moveElement(const std::string& src, const std::string& dest) {
    if (src.empty() || src == dest.substr(0, src.length())) {
        throw std::invalid_argument("invalid source location. source cannot be same or a subelement of destination \n");
    }

    Object* destination = get(dest);
    Object* source = get(src); 

    if (!destination || !source) {
        throw std::invalid_argument("no such element\n");
    }

    if (destination->getType() == PRIMITIVE) {
        upliftPrimitive(destination, dest);
    }

    removeElement(src, false);
    destination->addChild(RegexUtil::splitAtLastDot(src).second, source);
}

void JsonFile::sortArray(const std::string& str) {
    Object* obj = get(str);
    if (obj) {
        obj->sort();
    } else {
        throw std::invalid_argument("no such element");
    }
}


std::vector<Object*> JsonFile::findByKey(const std::string& key)const {
    std::vector<Object*> res;
    if (root) {
        root->findByKeyHelper(key, res);
    }
    return res;
}

void JsonFile::getAllByKey(const std::string& key, const std::string& destination)const {
    std::vector<Object*> objs = findByKey(key);
    Object* array = new ObjectArray();
    for (Object* obj : objs) {
        array->addChild("", obj);
    }

    if (destination.empty()) {
        print(array, std::cout, false);
    } else {
        std::ofstream out(destination);
        print(array, out, false);
    }

    delete array;
}

void JsonFile::getNthByKey(const std::string& key, const int& index, const std::string& destination)const {
    std::vector<Object*> objs = findByKey(key);
    if (index < 0 || index < objs.size()) {
        if (destination.empty()) {
            print(objs[index], std::cout, false);
        } else {
            std::ofstream out(destination);
            print(objs[index], out, false);
        }
    } else {
        throw new std::out_of_range("invalid index\n");
    }
}
