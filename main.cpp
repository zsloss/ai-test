#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string int_to_string(int x) {
    ostringstream ss;
    ss << x;
    return ss.str();
}

class Person {
    public:
        int hunger;
        string name;
        Person();
    private:
        static int people;
        int id;
};

int Person::people = 0;

Person::Person() {
    id = ++people; 
    name = "Person " + int_to_string(id);
}

int main(int argc, char* argv[]) {
    cout << "Hello, idiots!" << endl;
    Person p = Person();
    cout << p.name << endl;
}
