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
#include "wavetable.h"
#include "wavetablegroup.h"
#include "functiongenerators.h"
#include "clock.h"

Scope gScope;
WaveTableGroup gWave;
Clock gClock;

bool setup(BelaContext *context, void *userData) {
    unsigned int waveTableSize = 512;

    gWave.setup(waveTableSize, context->audioSampleRate);
    gClock.setup(context->audioSampleRate);

    FunctionGenerators funcs = FunctionGenerators(waveTableSize);

    std::vector<std::vector<float>> sampleData {
        funcs.generate(Functions::Saw),
                funcs.generate(Functions::Sine),
                funcs.generate(Functions::Triangle),
                funcs.generate(Functions::Pulse)
    };

    gWave.addWaveTables(sampleData);

    gScope.setup(2, context->audioSampleRate);

    auto helloFunc = [](){gWave.setFrequency(map((float)rand(), 0, (float)RAND_MAX, 440, 880));};
    gClock.triggerOnInterval(helloFunc, 1);

    gClock.triggerOnTimeout([]() {
        printf("hello!\n");
    }, 5);

    return true;
}

float cvToFreq(float in) {
    // TODO: Sample voltages across ranges
    float volts = in * 10.0;
    float hz = 73.42*powf(2.0, volts - 0.152);
    return hz;

}

void render(BelaContext *context, void *userData) {
  for (unsigned int n = 0; n < context->audioFrames; n++) {
    float input = analogRead(context, 0, 1);
    float transform = analogRead(context, 0, 2);
    // float freq = cvToFreq(input);
    // gWave.setFrequency(freq);
    gWave.setPosition(transform, 0, 1);

    float out = gWave.process();

    for (unsigned int channel = 0; channel < context->audioOutChannels;
         channel++) {
      audioWrite(context, n, channel, out);
    }

    gScope.log(out);
    gClock.tick();
  }
}

void cleanup(BelaContext *context, void *userData) {}
