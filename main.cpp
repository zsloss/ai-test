#include <iostream>
#include <string>
#include <sstream>
#include <random>

using namespace std;

string int_to_string(int x) {
    ostringstream ss;
    ss << x;
    return ss.str();
}

int rnd_gen(int min, int max) {
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<int> uni_dist(min, max);
    return uni_dist(generator);
}

class Person {
    public:
        int hunger;
        string name;
        Person();
        Person(string);
    private:
        static int people;
        int id;
};

int Person::people = 0;

Person::Person() {
    id = ++people; 
    name = "Person " + int_to_string(id);
}

Person::Person(string n) {
    Person();
    name = n;
}

int main(int argc, char* argv[]) {
    cout << "Hello, idiots!" << endl;
    Person p = Person("Twatmongrel");
   cout << rnd_gen(1, 6) << endl;
}


