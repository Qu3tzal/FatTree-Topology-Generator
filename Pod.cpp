#include "Pod.hpp"

#include <cmath>

Pod::Pod(unsigned int id, unsigned int numberOfPods)
    : m_id(id)
{
    // Create the aggregation switches.
    for(unsigned int i(0) ; i < numberOfPods / 2 ; ++i)
    {
        m_workstations.push_back(Node({id, i + numberOfPods / 2, 1}, NodeHardware::Switch, NodeType::Aggregation, numberOfPods));
    }

    // Create the edge switches.
    for(unsigned int i(0) ; i < numberOfPods / 2 ; ++i)
    {
        m_workstations.push_back(Node({id, i, 1}, NodeHardware::Switch, NodeType::Edge, numberOfPods));
    }

    // Create the workstations.
    for(unsigned int i(0), workstationId(id * std::pow(numberOfPods / 2, 2)) ; i < std::pow(numberOfPods / 2, 2) ; ++i, ++workstationId)
    {
        m_workstations.push_back(Node({workstationId, 0, 0}, NodeHardware::Hca, NodeType::Workstation, 1));
    }
}

Pod::~Pod()
{

}

void Pod::connectToCores(std::vector<Node>& cores)
{

}
