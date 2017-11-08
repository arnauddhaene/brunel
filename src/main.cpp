//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Experiment.h"

int main() {

    /// clock times
    clock_t t1, t2;

    t1 = clock();

    Experiment experiment("../results/rasterdataC.gdf");

    experiment.run(1000);

    t2 = clock();

    std::cout << "runtime : " << ((float) t2 - (float) t1) / CLOCKS_PER_SEC << " s" << '\n';

    return 0;
}
