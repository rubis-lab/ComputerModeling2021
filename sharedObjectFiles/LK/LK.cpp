#include "LK.h"

void sim_main()
{
  if (rtU->read2 <= 5000.0)
  {
    rtDW->w3 = 0.0;
    rtDW->w4 = 0.0;
  }
  else
  {
    if (rtU->read1 > 0.0)
    {
      rtDW->w3 = 0.0;
    }
    else if ((rtU->read1 < 0.0) && (rtU->read1 < -1000.0))
    {
      //rtDW->w3 = 10000.0;
      rtDW->w3 = 1000.0; // cap at 1000 to avoid over steering
    }
    else
    {
      if ((rtU->read1 < 0.0) && (rtU->read1 >= -1000.0))
      {
        //rtDW->w3 = rtU->read1 * -1;
        rtDW->w4 = 0.0;
        if(rtDW->w3 > rtU->read1) { // smooth steer
          rtDW->w3 -= 100.0;
        }
        else {
          rtDW->w3 += 100.0;
        }
      }
    }

    if ((rtU->read1 > 0.0) && (rtU->read1 > 1000.0))
    {
      //rtDW->w4 = 10000.0;
      rtDW->w4 = 1000.0; // cap at 1000 to avoid over steering
    }
    else if ((rtU->read1 > 0.0) && (rtU->read1 <= 1000.0))
    {
      //rtDW->w4 = rtU->read1;
      rtDW->w3 = 0.0;
      if(rtDW->w4 < rtU->read1) { // smooth steer
        rtDW->w4 += 100.0;
      }
      else {
        rtDW->w4 -= 100.0;
      }
    }
    else
    {
      if (rtU->read1 < 0.0)
      {
        rtDW->w4 = 0.0;
      }
    }
  }
  rtY->write3 = rtDW->w3;
  rtY->write4 = rtDW->w4;
}