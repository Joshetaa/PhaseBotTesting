#include "Arduino.h"

/** Gait
 * Defines a motion for a 4 legged robot in terms of
 * 3 angular offsets, one for each leg other than the leading leg.
 */ 
struct Gait
{
    // A short name, could be displayed on a HUD
    char name[7];
    
    // Right Lead leg is the angular reference point.
    // By convention, offsets[0] is always 0,
    // since the leading leg defines the offset.
    unsigned int offsets[4];
};

Gait bounding = {
    "BOUND",
    {0, 0, 180, 180}};

Gait trotting = {
    "TROT ",
    {0, 180, 0, 180}};

Gait pacing = {
    "PACE",
    {0, 180, 180, 0}};

// enumeration of legs, corresponding to `offsets` indices
enum legs
{
    R_LEAD = 0,
    L_LEAD = 1,
    L_HIND = 2,
    R_HIND = 3,
};