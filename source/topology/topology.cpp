#include "topology.h"

Topology::Topology(string ID, list<Component*>* components) {
    this->ID = ID;
    this->components = components;
}

void Topology::print() {
    cout << "************************************************" << endl;
    cout << "Topology ID: " << ID << endl;
    for (list<Component*>::iterator it = (*components).begin(); it != (*components).end(); it++) {
        (*it)->print();
    }
    cout << "************************************************" << endl;
}

string Topology::getID() {
    return ID;
}

list<Component*>* Topology::getComponents() {
    return components;
}


Topology::~Topology() {
    for (list<Component*>::iterator it = (*components).begin(); it != (*components).end(); it++) {
        delete *it;
    }
    components->clear();
    components = nullptr;
}