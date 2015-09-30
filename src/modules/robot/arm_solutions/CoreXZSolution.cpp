#include "CoreXZSolution.h"
#include <math.h>

#define z_reduction_checksum         CHECKSUM("z_reduction")

CoreXZSolution::CoreXZSolution(Config* config)
{
    z_reduction         = config->value(z_reduction_checksum)->by_default(3.0f)->as_number();
}

void CoreXZSolution::cartesian_to_actuator(const float cartesian_mm[], float actuator_mm[] ){
    actuator_mm[ALPHA_STEPPER] = cartesian_mm[X_AXIS] + (z_reduction * cartesian_mm[Z_AXIS]);
    actuator_mm[BETA_STEPPER ] = cartesian_mm[X_AXIS] - (z_reduction * cartesian_mm[Z_AXIS]);
    actuator_mm[GAMMA_STEPPER] = cartesian_mm[Y_AXIS];
}

void CoreXZSolution::actuator_to_cartesian(const float actuator_mm[], float cartesian_mm[] ){
    cartesian_mm[X_AXIS] = 0.5F * (actuator_mm[ALPHA_STEPPER] + actuator_mm[BETA_STEPPER]);
    cartesian_mm[Z_AXIS] = (0.5F/z_reduction) * (actuator_mm[ALPHA_STEPPER] - actuator_mm[BETA_STEPPER]);
    cartesian_mm[Y_AXIS] = actuator_mm[GAMMA_STEPPER];
}
