#include "experiment.h"

int main(void)
{
    Experiment experiment;

    if (!Experiment_Init(&experiment))
    {
        return 1;
    }

    Experiment_Run(&experiment);

    Experiment_Shutdown(&experiment);

    return 0;
}