#include "mind.h"

Mind::Mind(Person* _me, Body* _body) : id(_me->get_id()) {
    me = _me;
    body = _body;
}

void Mind::add_relation(int p_id) {
	relations.insert(std::pair<int, int>(p_id, 50));
}

bool Mind::knows(int p_id) {
	return relations.find(p_id) != relations.end();
}
