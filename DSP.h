#include "OpenAudio_ArduinoLibrary.h"
#include "AudioStream_F32.h"
#include "Hilbert.h"
#include <Audio.h>
#include <Wire.h>
#include "AudioFilterFIRGeneral_F32.h"

String Mode="LSB";

const float sample_rate_Hz = 48000.0f ;  // 24000, 44117, or other frequencies listed above
const int   audio_block_samples = 128;

AudioSettings_F32 audio_settings(sample_rate_Hz, audio_block_samples);

AudioInputI2S_F32        audioInI2S1; 
AudioFilterFIR_F32 filterFIRgeneral2; 
AudioFilterFIR_F32 filterFIRgeneral1; 
AudioMixer4_F32          mixer4_1;      
AudioOutputI2S_F32       audioOutI2S1;  

AudioConnection_F32          patchCord1(audioInI2S1, 0, filterFIRgeneral1, 0);
AudioConnection_F32          patchCord2(audioInI2S1, 1, filterFIRgeneral2, 0);
AudioConnection_F32          patchCord3(filterFIRgeneral1, 0, mixer4_1, 0);
AudioConnection_F32          patchCord4(filterFIRgeneral2, 0, mixer4_1, 1);
AudioConnection_F32          patchCord5(mixer4_1, 0, audioOutI2S1, 0);
AudioConnection_F32          patchCord6(mixer4_1, 0, audioOutI2S1, 1);

//AudioConnection_F32          patchCord10(audioInI2S1, 0, audioOutI2S1, 0);
//AudioConnection_F32          patchCord11(audioInI2S1, 1, audioOutI2S1, 1);


void initDsp()
{

//float32_t workspace[4128];

AudioMemory(20); // 16 bit audio memory allocation
AudioMemory_F32(50, audio_settings);

//filterFIRgeneral1.LoadCoeffs(101, Hilbert_Plus45_3000H,workspace);
//filterFIRgeneral2.LoadCoeffs(101, Hilbert_Minus45_3000H,workspace);

filterFIRgeneral1.begin(Hilbert_Plus45_3000N,101);   //Left Channel
filterFIRgeneral2.begin(Hilbert_Minus45_3000N,101);  //Right Channel

mixer4_1.gain(0,1.0);
mixer4_1.gain(1,-1.0);

}