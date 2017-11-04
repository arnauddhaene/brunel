//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Experiment.h"

int main() {

    Experiment experiment("rasterdataC.gdf");

    experiment.run(1000);

    return 0;
}
