//
//  Organ.hpp
//  AudioKit Core
//
//  Created by Shane Dunne, revision history on Github.
//  Copyright © 2018 AudioKit. All rights reserved.
//

#ifdef __cplusplus
#include <memory>

#define AKSYNTH_CHUNKSIZE 16            // process samples in "chunks" this size

class Organ
{
public:
    Organ();
    ~Organ();

    int init(double sampleRate);
    void deinit();

    void playNote(unsigned noteNumber, unsigned velocity, float noteFrequency);
    void stopNote(unsigned noteNumber, bool immediate);
    void sustainPedal(bool down);

    void setPitchOffset(float offset) { pitchOffset = offset; }
    float getPitchOffset() { return pitchOffset; }

    void setVibratoDepth(float depth) { vibratoDepth = depth; }
    float getVibratoDepth() { return vibratoDepth; }

    // Master volume: range 0 to 1, default 1.0
    void setMasterVolume(float vol);
    float getMasterVolume();

    // Velocity sensitivity: range 0 to 1, default 1.0
    void setVelocitySensitivity(float sens);
    float getVelocitySensitivity();

    // Tuning ratio: set e.g. 0.5 to play 1 octave below MIDI pitch
    void setTuningRatio(float ratio);
    float getTuningRatio();

    void  setAmpAttackDurationSeconds(float value);
    float getAmpAttackDurationSeconds(void);
    void  setAmpDecayDurationSeconds(float value);
    float getAmpDecayDurationSeconds(void);
    void  setAmpSustainFraction(float value);
    float getAmpSustainFraction(void);
    void  setAmpReleaseDurationSeconds(float value);
    float getAmpReleaseDurationSeconds(void);

    // 9 Hammond-style drawbars...
    void setDrawBar(int index, float value);
    float getDrawBar(int index);
    // ...OR 16 harmonic partials
    void setHarmonicLevel(int index, float value);
    float getHarmonicLevel(int index);

    // Distortion controls
    void setPower(float power); // typically 1.0 to 2.0
    float getPower();
    void setDrive(float drive); // typically 1.0 to 2.5
    float getDrive();
    void setGain(float gain);   // typically 1.0 to 2.5
    float getGain();

    // Leslie speed control: 1.0 to 8.0 (fractional part ignored)
    void setLeslieSpeed(float speed);
    float getLeslieSpeed();

    void render(unsigned channelCount, unsigned sampleCount, float *outBuffers[]);

protected:
 
    struct InternalData;
    std::unique_ptr<InternalData> data;

    // performance parameters
    float pitchOffset, vibratoDepth;

    // render-prep callback
    static void renderPrepCallback(void* thisPtr);
};

#endif
