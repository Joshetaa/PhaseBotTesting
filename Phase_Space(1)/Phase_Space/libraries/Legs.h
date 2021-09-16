#include <LSS.h>

// NOTE: these servo IDs are specific to Elijah's Robot
// may need to be changed at a later date.
#define R_LEAD_LEG_ID 1
#define L_LEAD_LEG_ID 2
#define L_HIND_LEG_ID 4
#define R_HIND_LEG_ID 3
// LSS Documentation
// https://www.robotshop.com/info/wiki/lynxmotion/view/lynxmotion-smart-servo/lss-communication-protocol/#HIdentificationNumber28ID29
#define BROADCAST_ID 254

LSS R_LEAD_LEG = LSS(R_LEAD_LEG_ID);
LSS L_LEAD_LEG = LSS(L_LEAD_LEG_ID);
LSS R_HIND_LEG = LSS(R_HIND_LEG_ID);
LSS L_HIND_LEG = LSS(L_HIND_LEG_ID);

// used to broadcast a command to all servos
LSS ALL = LSS(BROADCAST_ID); 

// array of servos, so they can be individually addressed in a `for` loop
LSS LSSs[4] = {
    R_LEAD_LEG,
    L_LEAD_LEG,
    L_HIND_LEG,
    R_HIND_LEG,
};

// Represents the adjustment made to each leg's virtul angular position,
// so that all legs are aligned in real space.
// Calibrated for each individual robot.
// Calibration offsets for Elijah's Robot
int cal[4] {
0,0,0,0
};
