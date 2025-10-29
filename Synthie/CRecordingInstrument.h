#pragma once
#include "CInstrument.h"
#include "CSineWave.h"
#include "audio/wave.h"
#include "audio/DirSoundSource.h"

class CRecordingInstrument :
    public CInstrument
{
public:
    CRecordingInstrument(void);
    ~CRecordingInstrument(void);

    virtual void Start();
    virtual bool Generate();

    void SetNote(CNote* note);

    void SetFreq(double f) { m_sinewave.SetFreq(f); }
    void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }
    void SetDuration(double d) { m_duration = d; }
    void SetEffects(CEffects e) override { m_effects = e; }
    //void SetFuzz(double f) override { m_fuzz = std::pow(f, 4)*1000; }
    void SetFuzz(double f) override { m_fuzz = f*9+1; }
    void ProcessReadFrame(short* p_frame);
    void SetSoundSource(CDirSoundSource* source) override { m_wavein = source; }

private:
    CSineWave m_sinewave;
    double m_duration;
    double m_time;
    double m_attackRelease;
    double   m_amplitude;
    double   m_sampleRate;
    int      m_numChannels;
    int      m_numSampleFrames;
    CDirSoundSource*   m_wavein;
    double oscillator;
    double m_fuzz;
    CEffects m_effects;
    short audio[2];
};

