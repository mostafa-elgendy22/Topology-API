#include <API.h>

int main() {
    API* api = new API();
   
    cout << "1- Read a topology from a JSON file and store it in the memory" << endl;
    cout << "2- Write a topology from the memory to a JSON file" << endl;
    cout << "3- Query about which topologies are currently in the memory" << endl;
    cout << "4- Delete a topology from the memory" << endl;
    cout << "5- Query about which devices are in a topology" << endl;
    cout << "6- Query about which devices are connected to a given netlist node in a topology" << endl;
    cout << "7- Exit program" << endl;
   
    while (1) {
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice > 7 || choice < 1) {
            cout << "Wrong choice" << endl;
            continue;
        }
        if (choice == 7) {
            break;
        }
        switch (choice)
        {
            case 1:
            {
                string fileName;
                cout << "Enter the name of the JSON file: ";
                cin >> fileName;
                if (api->readJSON(fileName)) {
                    cout << "The topology is added to the memory successfully" << endl;
                } else {
                    cout << "A topology with the same ID is already stored in the memory" << endl;
                }
                break;
            }
            case 2:
            {
                string topologyID;
                cout << "Enter the topology ID: ";
                cin >> topologyID;
                if (api->writeJSON(topologyID)) {
                    cout << "The topology of ID '" << topologyID << "' was successfully written to a JSON file" << endl;
                } else {
                    cout << "There is no topology with the given ID stored in the memory" << endl;
                } 
                break;
            }
            case 3:
            {
                list<Topology*>* topologies = api->queryTopologies();
                cout << "Number of topologies stored in the memory is " << topologies->size() << endl;
                for (list<Topology*>::iterator i = (*topologies).begin(); i != (*topologies).end(); i++) {
                    (*i)->print();
                }
                break;
            }
            case 4:
            {
                string topologyID;
                cout << "Enter the topology ID: ";
                cin >> topologyID;
                if (api->deleteTopology(topologyID)) {
                    cout << "The topology with ID '" << topologyID << "' is successfully deleted" << endl;
                } else {
                    cout << "There is no topology with the given ID stored in the memory" << endl;
                }
                break;
            }
            case 5:
            {
                string topologyID;
                cout << "Enter the topology ID: ";
                cin >> topologyID;
                list<Component*>* components = api->queryComponents(topologyID);
                if (components) {
                    for (list<Component*>::iterator i = (*components).begin(); i != (*components).end(); i++) {
                        (*i)->print();
                    }
                } else {
                    cout << "There is no topology with the given ID stored in the memory" << endl;
                }
                break;
            }
            
            case 6:
            {
                string topologyID, netlistNodeID;
                cout << "Enter the topology ID: ";
                cin >> topologyID;
                cout << "Enter the netlist node ID: ";
                cin >> netlistNodeID;
                list<Component*>* components = api->queryComponentsWithNetlistNode(topologyID, netlistNodeID);
                if (components) {
                    if (components->size() == 0) {
                        cout << "There are no components connected to the netlist node whose ID is '" << netlistNodeID << "'" << endl;
                    }
                    for (list<Component*>::iterator i = (*components).begin(); i != (*components).end(); i++) {
                        (*i)->print();
                    }
                } else {
                    cout << "There is no topology with the given ID stored in the memory" << endl;
                }
                break;
            }
        }
    }
    delete api;
    api = nullptr;
    return 0;
}