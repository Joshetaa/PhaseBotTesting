// Represents raw digital input from the FlySky receiver to the Arduino
struct RawInput
{
    // left Knob
    int lKnob;

    // right Knob
    int rKnob;

    // joystick
    int lStck;
};

// normalized input
struct Position
{
    // left Knob
    double lKnob;
    // right Knob
    double rKnob;
    // joystick
    double lStck;
};

// Represents the upper and lower bounds of signals from the FlySky remote.
// Meant to be calibrated to each individual FlySky remote controller's bounds.
struct Bounds
{
   // left knob bounds
    double lKnobMin;
    double lKnobMax;

    // right knob bounds
    double rKnobMin;
    double rKnobMax;

    // left joystick bounds
    double lStckMin;
    double lStckMax;
};

// Elijah's remote
Bounds remote1{
    17860, 18850,
    17857, 18850,
    17625, 18850};