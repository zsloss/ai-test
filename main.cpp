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
        void update();
    private:
        static int people;
        int id;
        void init();
};

int Person::people = 0;

void Person::init() {
    id = ++people; 
    hunger = 0;
    cout << name << " is born." << endl;
}

Person::Person() {
    name = "Person " + int_to_string(id);
    init();
}

Person::Person(string n) {
    name = n;
    init();
}

void Person::update() {
    hunger++;
    cout << ".";
}

int main(int argc, char* argv[]) {
    cout << "** AI TEST **" << endl << endl;
    Person p = Person("Crash Test Dummy");
    for (int i = 0; i < 100; i++)
        p.update();
}


