#include "Pod.hpp"

#include <cmath>

Pod::Pod(unsigned int id, unsigned int numberOfPods)
    : m_id(id)
{
    // Create the aggregation switches.
    for(unsigned int i(0) ; i < numberOfPods / 2 ; ++i)
    {
        m_aggregations.push_back(Node({id, i + numberOfPods / 2, 1}, NodeHardware::Switch, NodeType::Aggregation, numberOfPods));
    }

    // Create the edge switches.
    for(unsigned int i(0) ; i < numberOfPods / 2 ; ++i)
    {
        m_edges.push_back(Node({id, i, 1}, NodeHardware::Switch, NodeType::Edge, numberOfPods));
    }

    // Create the workstations.
    for(unsigned int i(0), workstationId(id * std::pow(numberOfPods / 2, 2)) ; i < std::pow(numberOfPods / 2, 2) ; ++i, ++workstationId)
    {
        m_workstations.push_back(Node({workstationId, 0, 0}, NodeHardware::Hca, NodeType::Workstation, 1));
    }

    // Connect Workstation to edges
    unsigned int currentWorkstation(0);
    for(unsigned int i(0) ; i < m_edges.size() ; ++i)
    {
        for(unsigned int j(2) ; j <= m_edges[i].getNumberOfPorts() ; j += 2)
        {
            m_edges[i].connectTo(&(m_workstations[currentWorkstation]), j, 1);
            currentWorkstation++;
        }
    }

    /*// Connect Edge to aggregations
    for(unsigned int i(0) ; i < m_edges.size() ; ++i)
    {

    }*/
}

Pod::~Pod()
{

}

void Pod::connectToCores(std::vector<Node>& cores)
{
   unsigned int currentCore(0);
   for(unsigned int i(0); i < m_aggregations.size(); ++i)
   {
       for(unsigned int j(1) ; j <= (m_aggregations[i].getNumberOfPorts()); j += 2)
       {
           m_aggregations[i].connectTo(&(cores[currentCore]), j, m_id + 1);
           currentCore++;
       }
   }
}
