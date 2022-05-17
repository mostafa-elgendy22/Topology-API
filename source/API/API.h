#pragma once

#include <list>
#include <fstream>
#include <json/json.hpp>
#include <topology.h>
#include <resistor.h>
#include <NMOS.h>

typedef nlohmann::ordered_json json;

class API {
private:

    /**
     * @brief A list the saves the addresses of the topologies that are currently stored in the memory
     */
    list<Topology*>* topologies;

    /** This function is used by many member functions to find a topology with a certain ID and it is a private function because it is considered as non-core functionality for the API
     * @brief A utility function that returns a pointer to a topology given its ID
     * @param topologyID The ID of required topology to be returned
     * @return The address of the topology object
     */
    Topology* getTopologyFromID(string topologyID);

public:

    /** Construct a new API object with an empty list of topology pointers
     * @brief Default constructor
     */
    API();

    /** This function reads a topology JSON file which is located in "topology_input_files" directory and store the object in the memory 
     * @brief Stores a topology in the memory
     * @param fileName The name of the topology json file (for example: "topology1.json")
     * @return true if the topology is stored in the memory successfully
     * @return false if there is another topology stored in the memory with the same ID of the topology in the input JSON file
     */
    bool readJSON(string fileName);

    /** This function writes a topology of given ID to a JSON file, the name of the file is the same as the ID of the topology and the output file is located in "topology_output_directory" directory
     * @brief Writes a topology to a JSON file
     * @param topologyID The ID of the topology to be written in the JSON file
     * @return true if the topology is written successfully to the JSON file
     * @return false if there is no topology with the given ID stored in the memory
     */
    bool writeJSON(string topologyID);

    /**
     * @brief Query about the topologies stored in the memory
     * @return A list of addresses of the topologies that are currently stored in the memory
     */
    list<Topology*>* queryTopologies();

    /**
     * This function deletes a topology of given ID from the memory and delete its address from the list of saved topology addresses
     * @brief Delete a toplogy from the memory
     * @param topologyID The ID of the topology to be deleted
     * @return true if the topology is deleted successfully from the memory
     * @return false if there is no topology with the given ID stored in the memory
     */
    bool deleteTopology(string topologyID);

    /**
     * This function searches for a topology of given ID using the private member function 'getTopologyFromID' and returns its components if the topology exists otherwise it returns a null pointer (if there is no topology with the given ID)
     * @brief Query about the components of a topology
     * @param topologyID The ID of the topology that contains the required componenets
     * @return A list of Component object addresses (the addresses may be of an 'NMOS' or a 'Resistor' object)
     */
    list<Component*>* queryComponents(string topologyID);

    /**
     * This function searches for a topology of given ID using the private member function 'getTopologyFromID' and iterates through its components and filter them according to whether or not the component is connect to the netlist node of given ID and returns a list of the filtered components (the size of the returned list maybe zero if there are no components connected to the given netlist node), the function may return null pointer if there is no topology of the given ID stored in the memory 
     * @brief Query about components of a topology that are connected to a netlist node
     * @param topologyID The ID of the topology that contains the required componenets
     * @param netlistNodeID The ID of the netlist node that the required components are connected to
     * @return A list of Component object addresses (the addresses may be of an 'NMOS' or a 'Resistor' object)
     */
    list<Component*>* queryComponentsWithNetlistNode(string topologyID, string netlistNodeID);

    /**
     * @brief Destroy the API object by deleting all the topology objects pointed to by the pointers of the saved topologies (in the list) and then clearing the list of the topology pointers
     */
    ~API();
};