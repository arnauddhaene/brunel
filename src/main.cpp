//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Experiment.h"

int main() {


    /// clock times
    clock_t t1, t2;

    t1 = clock();

    Experiment experiment("../saved/rasterdataC.gdf");

    experiment.run(1000);

    t2 = clock();

    std::cout << "Total execution time : " << ((float) t2 - (float) t1) / CLOCKS_PER_SEC << " seconds" << '\n';

    return 0;
}
