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

#include <Bela.h>
#include <cmath>
#include <Scope/Scope.h>
#include <Utilities.h>
#include <stdlib.h>
#include "wavetable.h"
#include "wavetablegroup.h"


WaveTableGroup gWave;
Scope gScope;

const unsigned int kWaveTableSize = 512;

bool setup(BelaContext *context, void *userData) {
  std::vector<float> sineTable;
  sineTable.resize(kWaveTableSize);

  std::vector<float> sawTable;
  sawTable.resize(kWaveTableSize);

  Wavetable sine = Wavetable();
  Wavetable saw = Wavetable();

  for (unsigned int n = 0; n < sineTable.size(); n++) {
    sineTable[n] = sinf(2.0 * M_PI * (float)n / (float)sineTable.size());
  }

  for (unsigned int n = 0; n < sawTable.size(); n++) {
    sawTable[n] = (float)n / (float)sawTable.size();
  }

  sine.setup(context->audioSampleRate, sineTable);
  saw.setup(context->audioSampleRate, sawTable);

  gWave.addWaveTable(sine);
  gWave.addWaveTable(saw);
  gWave.setFrequency(440.0);
  gScope.setup(2, context->audioSampleRate);

  printf("I've been initialized\n");

  return true;
}

float cvToFreq(float in) {
    // TODO: Sample voltages across rangesr
    float volts = in * 10.0;
    float hz = 73.42*powf(2.0, volts - 0.152);
    return hz;

}

void render(BelaContext *context, void *userData) {
  for (unsigned int n = 0; n < context->audioFrames; n++) {
    float input = analogRead(context, 0, 1);
    float freq = cvToFreq(input);

    gWave.setFrequency(freq);

    float out = gWave.process();

    for (unsigned int channel = 0; channel < context->audioOutChannels;
         channel++) {
      audioWrite(context, n, channel, out);
    }

    gScope.log(out);
  }
}

void cleanup(BelaContext *context, void *userData) {}
