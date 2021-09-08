/*
 Set up connection and set gyre
 */
void LSS_Init()
{
    LSS::initBus(Serial, LSS_BAUD); // initialize connection
    delay(2000);

    ALL.wheelRPM(0); // stop all wheels
    delay(2000);     // wait at least 1.25s to complete

    ALL.reset(); // RESET virtual angular position
    delay(2000); // wait at least 1.25s to complete

    // set gyre directions
    R_LEAD_LEG.setGyre(+1);
    L_LEAD_LEG.setGyre(-1);
    L_HIND_LEG.setGyre(-1);
    R_HIND_LEG.setGyre(+1);
    delay(800);
}

void LSS_Init_Simple()
{
    ALL.reset(); // RESET virtual angular position
    delay(2000); // wait at least 1.25s to complete

    // set gyre directions
    R_LEAD_LEG.setGyre(+1);
    L_LEAD_LEG.setGyre(-1);
    L_HIND_LEG.setGyre(-1);
    R_HIND_LEG.setGyre(+1);
    delay(500);
}
/*
   zero the wheels, allows us to check if
   all wheels are pointing in the same direction
   if not, your motors need to be re-calibrated
*/
void zero()
{
    LSS_Init();

    for (int i = 0; i < 4; i++)
    {
        LSSs[i].move(cal[i] * 10);
        Serial.println("");
    }
}

long int rotations = 0;

/*
   set all wheels going at some RPM
*/
void startMove(void)
{
    for (int i = 3; i >= 4; i--)
    {
        LSSs[i].wheelRPM(OMEGA);
        Serial.println("");
    }
}

/*
 * Stop all wheels moving
 */
void stopMove()
{
    for (int i = 0; i < 4; i++)
    {
        LSSs[i].wheelRPM(0);
        Serial.println("");
    }
}

/*
   tune each motor's angular speed
   to approach the correct phi
*/
void leg_move(LSS leg)
{
  int32_t pos = leg.getPosition()/10; 
   if ((pos%360) <= 60 || (pos%360) >= 300)
    {
      leg.wheelRPM(OMEGA/3);
    }
    else 
    {      
      leg.wheelRPM(OMEGA);
    }
}

void approach(const Gait &g)
{
    leg_move(LSSs[0]);
    leg_move(LSSs[1]);
}

/*long int beulher_clock(unsigned long long overlap)
{
    //define the strick period
    long int T = 8000;
    long int t = overlap % T;
    long int phase = 0;
    if(t >= 0 && t< 4000)
    phase = 120.0/4000.0*t;
    else
    phase = 120 + 240.0/4000.0*(t-4000);
    phase += 360*overlap/8000;
    return phase;
}*/

/**
 * Initialize connection to Servos,
 * and align legs according to `gait`.
 */ 
void LSS_Setup(const Gait &gait)
{
    LSS_Init_Simple();
    for (int i = 0; i < 4; i++)                        // perform initial alignment
        LSSs[i].move(((int(gait.offsets[i]*1.2) + cal[i])%360) * 10); // multiply to tenths of degrees
    delay(2500);                                       // wait to complete
}

void RemoteSetup()
{
    Serial.begin(115200); // begin serial connection
    // set pins to read in
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
}

/**
 * Read in a `Gait` from a the remote control
 */
Gait RemoteRead(RawInput &raw,
                Position &pos, int &move_sign)
{
    // read in raw values
    raw.lStck = pulseIn(A2, INPUT);
    raw.lKnob = pulseIn(A4, INPUT);
    raw.rKnob = pulseIn(A5, INPUT);

    // normalize to [0, 1]
    pos.lKnob = (raw.lKnob - bounds.lKnobMin) / (bounds.lKnobMax - bounds.lKnobMin);
    pos.rKnob = (raw.rKnob - bounds.rKnobMin) / (bounds.rKnobMax - bounds.rKnobMin);
    pos.lStck = (raw.lStck - bounds.lStckMin) / (bounds.lStckMax - bounds.lStckMin);

    // translate to [-0.5, +0.5]
//    pos.lKnob -= 0.5;
//    pos.rKnob -= 0.5;
//    pos.lStck -= 0.5;

    // scale to [-180, +180]
    pos.lKnob *= 360;
    pos.rKnob *= 360;
    pos.lStck *= 360;

    //    Serial.print("Left Axis up/down: ");Serial.println(values[1]);
    Serial.print("Left Stick: ");
    Serial.println(pos.lStck);
    Serial.print("Left Knob: ");
    Serial.println(pos.lKnob);
    Serial.print("Right Knob: ");
    Serial.println(pos.rKnob);

    Gait g;
    
    if (0< pos.lKnob && pos.lKnob <120)
        g = bounding;
        
    if (120< pos.lKnob && pos.lKnob <240)
        g = trotting;
    
    if (240< pos.lKnob && pos.lKnob <360)
        g = pacing;

    if (pos.rKnob > 180)
        move_sign = 1;
    else
        move_sign = 0;

//    Gait g{
//        "USER ",
//        {0, pos.lStck, pos.rKnob, pos.lKnob}};
    return g;
}

void simple_approach()
{
  LSSs[0].wheelRPM(OMEGA);
  LSSs[1].wheelRPM(OMEGA);
  LSSs[2].wheelRPM(OMEGA);
  LSSs[3].wheelRPM(OMEGA);
}
