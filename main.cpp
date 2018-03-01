#include <iostream>
#include <cstdlib>

#include "FatTree.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    unsigned int numberOfPods(0);

    // We check that we have at least two arguments.
    if(argc > 1)
    {
        // We get the number of pods.
        numberOfPods = atoi(argv[1]);

        // We create a fat tree.
        FatTree ft(numberOfPods);

        // We serialize.
        ft.serialize("fattree.topo");
    }

    return 0;
}
