/*
 ____  _____ _        _
| __ )| ____| |      / \
|  _ \|  _| | |     / _ \
| |_) | |___| |___ / ___ \
|____/|_____|_____/_/   \_\

The platform for ultra-low latency audio and sensor processing

http://bela.io

A project of the Augmented Instruments Laboratory within the
Centre for Digital Music at Queen Mary University of London.
http://www.eecs.qmul.ac.uk/~andrewm

(c) 2016 Augmented Instruments Laboratory: Andrew McPherson,
        Astrid Bin, Liam Donovan, Christian Heinrichs, Robert Jack,
        Giulio Moro, Laurel Pardue, Victor Zappi. All rights reserved.

The Bela software is distributed under the GNU Lesser General Public License
(LGPL 3.0), available here: https://www.gnu.org/licenses/lgpl-3.0.txt
*/

#include "wavetable.h"
#include <Bela.h>
#include <cmath>
#include <Scope/Scope.h>
#include <Utilities.h>

Wavetable gOscillator;
Scope gScope;

const unsigned int kWaveTableSize = 512;

bool setup(BelaContext *context, void *userData) {
  std::vector<float> wavetable;
  wavetable.resize(kWaveTableSize);
  gOscillator = Wavetable();

  for (unsigned int n = 0; n < wavetable.size(); n++) {
    wavetable[n] = sinf(2.0 * M_PI * (float)n / (float)wavetable.size());
  }

  gOscillator.setup(context->audioSampleRate, wavetable);
  gOscillator.setFrequency(440.0);
  gScope.setup(2, context->audioSampleRate);

  return true;
}

float cvToFreq(float in) {
    gScope.log(in);
    return 55.0*powf(2.0, in * 10);


}

void render(BelaContext *context, void *userData) {
  for (unsigned int n = 0; n < context->audioFrames; n++) {
    float out = gOscillator.process();
    float input = analogRead(context, 0, 1);
    float freq = cvToFreq(input);
    gOscillator.setFrequency(freq);

    for (unsigned int channel = 0; channel < context->audioOutChannels;
         channel++) {
      audioWrite(context, n, channel, out);
    }
  }
}

void cleanup(BelaContext *context, void *userData) {}
