
#include <Wire.h>
#include <si5351.h> 
#include <Encoder.h>
Si5351 si5351;
Encoder Tune(16,15);

extern void displayFrequency();
extern void displayStep();


volatile uint32_t Frequency=7254000;
volatile uint32_t Step=1000;
long oldF  = -999;
long newF;    
int n=0;

uint32_t F_Upper=30000000; // default power up frequency
uint32_t F_Lower=1000000;


//////////////////////////Initialize VFO/DDS//////////////////////////////////////////////////////
void initVfo()
{
 delay(50);
 si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
 si5351.set_correction(33000, SI5351_PLL_INPUT_XO);//33000 is the calibration factor for my si5351
 si5351.set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
 si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_6MA);
 si5351.set_freq(Frequency *400ULL , SI5351_CLK0); 
}

void SetFrequency()
{ 
   si5351.set_freq((Frequency) *400ULL, SI5351_CLK0); // generating 4 x frequency ... set 400ULL to 100ULL for 1x frequency
   Serial.println(Frequency);
}


/************************TUNING ENCODER***************************************************/


void changeFrequency()
{
   newF = Tune.read()/4;

   if (newF != oldF)
  {
    /////////////////////////////////////////////////////
    if(newF>oldF)
      {
          Frequency=Frequency+Step;
          if (Frequency>F_Upper)
          {
            Frequency=F_Upper;
          }
     
      }
      ///////////////////////////////////////
      if(newF<oldF)
      {
        Frequency=Frequency-Step;
           if(Frequency<F_Lower)
           {
           Frequency=F_Lower;
           }
        
      }
         SetFrequency(); 
         displayFrequency();
         oldF = newF;
}

}

void setStep()
{   
     if(digitalRead(17)==LOW)  //Switch pushed ??
    {  
      delay(500);  //debounce

      if(n==0)  
      {
        Step=1000;  //select step  
      }
    
      if(n==1)
      {
        Step=100;  //select step
      }

      if(n==2)
      {
        Step=10;  //select step
      }

      if(n==3)
      {
        Step=1;  //select step
      }

      if(n==4)
      {
        n=0;   // no more steps
      }
      else
      {
        n=n+1; // still steps left
      }
      delay(100);
      DisplayStep();
    }
    
}
     
