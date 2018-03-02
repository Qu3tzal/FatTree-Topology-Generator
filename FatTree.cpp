#include "FatTree.hpp"

#include <iostream>
#include <fstream>
#include <cmath>

FatTree::FatTree(unsigned int numberOfPods)
    : m_numberOfPods(numberOfPods)
{
    // Generate the core nodes.
    for(unsigned int i(0) ; i < std::pow(numberOfPods / 2, 2) ; ++i)
    {
        m_cores.push_back(new Node({numberOfPods, i, 0}, NodeHardware::Switch, NodeType::Core, numberOfPods));
    }

    // Generate the pods.
    for(unsigned int i(0) ; i < numberOfPods ; ++i)
    {
        m_pods.push_back(new Pod(i, numberOfPods));
    }

    // Connect the pods to the cores.
    for(unsigned int i(0) ; i < numberOfPods ; ++i)
    {
        m_pods[i]->connectToCores(m_cores);
    }
}

FatTree::~FatTree()
{
    for(auto it = m_pods.begin(); it != m_pods.end(); it++)
        delete *it;
}

/**
 * @brief Helper function to print node links.
 * @param a reference to a node
 */
void printNodeLinks(Node& n, std::ostream& stream)
{
    unsigned int j(0);
    for(NodeLink& nl : n.getLinks())
    {
        j++;
        if(nl.node == nullptr)
            continue;

       // std::cout << "nl.node: " << nl.node << std::endl;
        stream << "[" << j << "] \"" << nl.node->getName() << "\"[" << nl.portNumber << "]" << std::endl;
    }
    stream << std::endl;
}

void FatTree::serialize(const std::string& filepath)
{

    std::ofstream file(filepath);
    if(!file)
    {
        std::cout << "Erreur lors de l'ouverture du fichier";
        return ;
    }

    std::cout << "writting" << std::endl;
    file << "#Fat tree topology file." << std::endl << "#Value of k = " << m_numberOfPods << std::endl;
    file << "#Total number of hosts = " << (m_numberOfPods * (std::pow(m_numberOfPods / 2, 2))) << std::endl;
    file << "#Number of hosts under each switch = " << m_numberOfPods / 2 << std::endl;
    file << "############################################" << std::endl << std::endl;

    // List the core nodes.
    for(unsigned int i(0) ; i < m_cores.size() ; ++i)
    {
        std::string hw = (m_cores[i]->getHardware() == NodeHardware::Hca) ? "Hca" : "Switch";
        file << hw << "\t" << m_cores[i]->getNumberOfPorts() << "\t\"" << m_cores[i]->getName() << "\"" << std::endl;
        printNodeLinks(*m_cores[i], file);
    }

    file << std::endl;

    // List the edge + aggregation.
    for(unsigned int i(0) ; i < m_pods.size() ; ++i)
    {
        for(Node * n : m_pods[i]->getEdge())
        {
            std::string hw = (n->getHardware() == NodeHardware::Hca) ? "Hca" : "Switch";
            file << hw << "\t" << n->getNumberOfPorts() << "\t\"" << n->getName() << "\"" << std::endl;
            printNodeLinks(*n, file);
        }

        file << std::endl;

        for(Node * n : m_pods[i]->getAggregation())
        {
            std::string hw = (n->getHardware() == NodeHardware::Hca) ? "Hca" : "Switch";
            file << hw << "\t" << n->getNumberOfPorts() << "\t\"" << n->getName() << "\"" << std::endl;
            printNodeLinks(*n, file);
        }
    }

    file << std::endl;

    // List the workstations.
    for(unsigned int i(0) ; i < m_pods.size() ; ++i)
    {
        for(Node * n : m_pods[i]->getWorkstation())
        {
            std::string hw = (n->getHardware() == NodeHardware::Hca) ? "Hca" : "Switch";
            file << hw << "\t" << n->getNumberOfPorts() << "\t\"" << n->getName() << "\"" << std::endl;
            printNodeLinks(*n, file);
        }
    }
    std::cout << "succes" << std::endl;
}
