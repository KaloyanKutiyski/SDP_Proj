main.out: main.o UI.o JsonFile.o composite.o objectArray.o primitive.o object.o RegexUtil.o
	g++ -std=c++17 main.o UI.o JsonFile.o composite.o objectArray.o primitive.o object.o RegexUtil.o -o main.out
	rm *.o

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

UI.o: UI/UI.cpp
	g++ -std=c++17 -c UI/UI.cpp

JsonFile.o: JSON_File/JsonFile.cpp
	g++ -std=c++17 -c JSON_File/JsonFile.cpp

composite.o: Object/Composite/composite.cpp
	g++ -std=c++17 -c Object/Composite/composite.cpp

objectArray.o: Object/ObjectArray/objectArray.cpp
	g++ -std=c++17 -c Object/ObjectArray/objectArray.cpp

primitive.o: Object/Primitive/primitive.cpp
	g++ -std=c++17 -c Object/Primitive/primitive.cpp

object.o: Object/object.cpp
	g++ -std=c++17 -c Object/object.cpp

RegexUtil.o: Util/RegexUtil.cpp
	g++ -std=c++17 -c Util/RegexUtil.cpp
