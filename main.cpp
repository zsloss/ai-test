#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <vector>

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
        void inform(string);
        void inform(Person&, string);
        void eat();
        void greet(Person&);
    private:
        static int people;
        int id;
        void init();
        Person *interacting;
};

int Person::people = 0;

void Person::init() {
    id = ++people; 
    if (name.empty())
        name = "Person " + int_to_string(id);
    hunger = 0;
    cout << name << " is born." << endl;
}

Person::Person() {
    init();
}

Person::Person(string n) {
    name = n;
    init();
}

void Person::update() {
    hunger++;
    if (hunger > 75) inform("hungry");
}

void Person::inform(string msg) {
    if (msg == "hungry") {
        if (rnd_gen(1, 100) < hunger)
            eat();
    }
    else cerr << "Error: Unknown inform message" << endl;
}

void Person::inform(Person &p, string msg) {
    if (msg == "enters")
        greet(p);
    else if (msg == "greets") {
        if (interacting->id != p.id)
            greet(p);
    }
    else cerr << "Error: Unknown inform message" << endl;
}

void Person::eat() {
    hunger = 0;
    cout << name << " eats." << endl;
}

void Person::greet(Person &p) {
    cout << name << ": \"Hello, " << p.name << "!\"" << endl;
    interacting = &p;
    p.inform(*this, "greets");
}

int main(int argc, char* argv[]) {
    cout << "** AI TEST **" << endl << endl;
    Person p1 = Person();
    for (int i = 0; i < 100; i++)
        p1.update();
    Person p2 = Person();
    p1.inform(p2, "enters");
    vector<Person> people = {Person(), Person()};
}


