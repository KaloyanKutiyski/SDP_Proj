test.out: test.o JsonFile.o composite.o objectArray.o primitive.o object.o RegexUtil.o
	g++ -std=c++17 test.o JsonFile.o composite.o objectArray.o primitive.o object.o RegexUtil.o -o test.out

test.o: test.cpp
	g++ -std=c++17 -c test.cpp

JsonFile.o: ../JSON_File/JsonFile.cpp
	g++ -std=c++17 -c ../JSON_File/JsonFile.cpp

composite.o: ../Object/Composite/composite.cpp
	g++ -std=c++17 -c ../Object/Composite/composite.cpp

objectArray.o: ../Object/ObjectArray/objectArray.cpp
	g++ -std=c++17 -c ../Object/ObjectArray/objectArray.cpp

primitive.o: ../Object/Primitive/primitive.cpp
	g++ -std=c++17 -c ../Object/Primitive/primitive.cpp

object.o: ../Object/object.cpp
	g++ -std=c++17 -c ../Object/object.cpp

RegexUtil.o: ../Util/RegexUtil.cpp
	g++ -std=c++17 -c ../Util/RegexUtil.cpp
