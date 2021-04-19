/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 8: Filters
sample-player-filter: template code for implementing digital filters
*/

#include <Bela.h>
#include "MonoFilePlayer.h"
#include "secondorderlpf.h"

// Name of the sound file (in project folder)
std::string gFilename = "../../../tmp/sample-player-filter/slow-drum-loop.wav";

// Object that handles playing sound from a buffer
MonoFilePlayer gPlayer;

SecondOrderLPF gLPF;

// TODO: declare global variable(s) to keep track of filter state

bool setup(BelaContext *context, void *userData)
{
	// Load the audio file
	if(!gPlayer.setup(gFilename)) {
    	rt_printf("Error loading audio file '%s'\n", gFilename.c_str());
    	return false;
	}

	// Print some useful info
    rt_printf("Loaded the audio file '%s' with %d frames (%.1f seconds)\n", 
    			gFilename.c_str(), gPlayer.size(),
    			gPlayer.size() / context->audioSampleRate);

	gLPF.setup(context->audioSampleRate);

	return true;
}

float cvToFreq(float in) {
    // TODO: Sample voltages across ranges
    float volts = in * 10.0;
    float hz = 100.0 * powf(2.0, in * (log(5000.0/100.0)) / log(2.0));
    return hz;

}

void render(BelaContext *context, void *userData)
{
    for(unsigned int n = 0; n < context->audioFrames; n++) {
        float filterFreq = cvToFreq(analogRead(context, 0, 1));
        float filterQ = map(analogRead(context, 0, 2), 0, 1, 0.5, 10);
        float in = gPlayer.process();

        float out = gLPF.process(in, filterQ, filterFreq);
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
