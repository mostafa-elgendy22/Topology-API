#pragma once

#include <list>
#include <component.h>
#include <string>

class Topology {
private:

    /**
     * @brief The ID of the topology
     */
    string ID;

    /**
     * @brief A list the saves the addresses of the components that are contained in the topology
     */
    list<Component*>* components;

public:

    /**
     * Construct a new Topology object and sets its parameters with the sent parameters
     * @brief Create a new Topology object
     * @param ID The ID of the topology
     * @param components A list of component pointers to create a topology
     */
    Topology(string ID, list<Component*>* components);

    /**
     * @brief Prints the ID of the topology and the components by iterating through the list of components and calling Component::print() (a virtual function)
     */
    void print();

    /**
     * @brief Gets the ID of the topology
     * @return ID The ID of the topology 
     */
    string getID();

    /**
     * @brief Get the components of the topology
     * @return A list of component pointers 
     */
    list<Component*>* getComponents();

    /**
     * @brief Destroy the Topology object by deleting all the Component objects pointed to by the pointers of the saved components (in the list) and then clearing the list of the component pointers
     */
    ~Topology();
};