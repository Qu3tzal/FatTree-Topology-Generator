#include "FatTree.hpp"

#include <iostream>
#include <cmath>

FatTree::FatTree(unsigned int numberOfPods)
    : m_numberOfPods(numberOfPods)
{
    // Generate the core nodes.
    for(unsigned int i(0) ; i < std::pow(numberOfPods / 2, 2) ; ++i)
    {
        m_cores.push_back(Node({numberOfPods, i, 0}, NodeHardware::Switch, NodeType::Core, numberOfPods));
    }

    // Generate the pods.
    for(unsigned int i(0) ; i < numberOfPods ; ++i)
    {
        m_pods.push_back(Pod(i, numberOfPods));
    }

    // Connect the pods to the cores.
    for(unsigned int i(0) ; i < numberOfPods ; ++i)
    {
        m_pods[i].connectToCores(m_cores);
    }
}

FatTree::~FatTree()
{
}

void FatTree::serialize(const std::string& filepath)
{
    std::cout << "Listing..." << std::endl;

    // List the core nodes.
    for(unsigned int i(0) ; i < m_cores.size() ; ++i)
    {
        std::string hw = (m_cores[i].getHardware() == NodeHardware::Hca) ? "Hca" : "Switch";
        std::cout << hw << "\t" << m_cores[i].getNumberOfPorts() << "\t\"" << m_cores[i].getName() << "\"" << std::endl;
    }

    std::cout << std::endl;

    // List the workstations.
    for(unsigned int i(0) ; i < m_pods.size() ; ++i)
    {
        for(Node& n : m_pods[i].getWorkstation())
        {
            std::string hw = (n.getHardware() == NodeHardware::Hca) ? "Hca" : "Switch";
            std::cout << hw << "\t" << n.getNumberOfPorts() << "\t\"" << n.getName() << "\"" << std::endl;
        }
    }

    std::cout << "Workstation end" << std::endl;
    std::cout << "Printing edge and aggregation" << std::endl;

    // List the edge + aggregation.
    for(unsigned int i(0) ; i < m_pods.size() ; ++i)
    {
        for(Node& n : m_pods[i].getEdge())
        {
            std::string hw = (n.getHardware() == NodeHardware::Hca) ? "Hca" : "Switch";
            std::cout << hw << "\t" << n.getNumberOfPorts() << "\t\"" << n.getName() << "\"" << std::endl;
        }

        for(Node& n : m_pods[i].getAggregation())
        {
            std::string hw = (n.getHardware() == NodeHardware::Hca) ? "Hca" : "Switch";
            std::cout << hw << "\t" << n.getNumberOfPorts() << "\t\"" << n.getName() << "\"" << std::endl;
        }
    }
}
