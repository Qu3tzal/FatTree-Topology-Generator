#include "Pod.hpp"

#include <cmath>

Pod::Pod(unsigned int id, unsigned int numberOfPods)
    : m_id(id)
{
    // Create the aggregation switches.
    for(unsigned int i(0) ; i < numberOfPods / 2 ; ++i)
    {
        m_aggregations.push_back(new Node({id, i + numberOfPods / 2, 1}, NodeHardware::Switch, NodeType::Aggregation, numberOfPods));
    }

    // Create the edge switches.
    for(unsigned int i(0) ; i < numberOfPods / 2 ; ++i)
    {
        m_edges.push_back(new Node({id, i, 1}, NodeHardware::Switch, NodeType::Edge, numberOfPods));
    }

    // Create the workstations.
    for(unsigned int i(0), workstationId(id * std::pow(numberOfPods / 2, 2)) ; i < std::pow(numberOfPods / 2, 2) ; ++i, ++workstationId)
    {
        m_workstations.push_back(new Node({workstationId, 0, 0}, NodeHardware::Hca, NodeType::Workstation, 1));
    }

    // Connect Workstation to edges
    unsigned int currentWorkstation(0);
    for(unsigned int i(0) ; i < m_edges.size() ; ++i)
    {
        unsigned int portNumber(2);
        for(unsigned int j(0) ; j < m_edges[i]->getNumberOfPorts() / 2 ; j++)
        {
            m_edges[i]->connectTo(m_workstations[currentWorkstation], portNumber, 1);
            currentWorkstation++;
            portNumber += 2;
        }
    }

    // Connect Edge to aggregations
    for(unsigned int i(0), agregationPort(2); i < m_edges.size() ; ++i, agregationPort += 2)
    {
        unsigned int agregationNumber(0);
        unsigned int edgePort(1);
        for(unsigned int j(0) ; j < m_edges[i]->getNumberOfPorts() / 2 ;j++)
        {
            m_edges[i]->connectTo(m_aggregations[agregationNumber], edgePort, agregationPort);
            agregationNumber++;
            edgePort += 2;
        }
    }
}

Pod::~Pod()
{
    for(auto it = m_aggregations.begin(); it != m_aggregations.end() ; it++)
        delete *it;
    for(auto it = m_edges.begin(); it != m_edges.end() ; it++)
        delete *it;
    for(auto it = m_workstations.begin(); it != m_workstations.end() ; it++)
        delete *it;
}

void Pod::connectToCores(std::vector<Node*>& cores)
{
   unsigned int currentCore(0);
   for(unsigned int i(0); i < m_aggregations.size(); ++i)
   {
       unsigned int portNumber(1);
       for(unsigned int j(0) ; j < (m_aggregations[i]->getNumberOfPorts() / 2); j++)
       {
           m_aggregations[i]->connectTo((cores[currentCore]), portNumber, m_id + 1);
           currentCore++;
           portNumber += 2;
       }
   }
}
