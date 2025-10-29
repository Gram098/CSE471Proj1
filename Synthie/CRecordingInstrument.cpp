#include "pch.h"
#include "CRecordingInstrument.h"
#include "Notes.h"
#include <iostream>
#include <filesystem>
#include <string>
#include "CEffects.h"

using namespace::std;
namespace fs = std::filesystem;

CRecordingInstrument::CRecordingInstrument(void) {
    m_duration = 0.1;
    m_attackRelease = .05;
    m_numChannels = 2;
    m_sampleRate = 44100.;
    m_numSampleFrames = 0;
    m_amplitude = .00001;
    oscillator = 0;
    m_fuzz = 0;
}

CRecordingInstrument::~CRecordingInstrument(void) {

}

void CRecordingInstrument::Start()
{
    m_sinewave.SetSampleRate(GetSampleRate());
    m_sinewave.Start();
    m_time = 0;
}


bool CRecordingInstrument::Generate()
{
    
    // Tell the component to generate an audio sample
    if (oscillator > (1 / m_sampleRate)) {
        ProcessReadFrame(audio);

        m_frame[0] = (double(audio[0]) * m_amplitude);
        if (m_numChannels == 1) {
            m_frame[1] = double(m_frame[0]);
        }
        else {
            m_frame[1] = (double(audio[1]) * m_amplitude);
        }
        if (m_fuzz > 1) {
            m_frame[0] *= 100;
            m_frame[1] *= 100;
            m_frame[0] = (tanh(m_frame[0] * m_fuzz) / tanh(m_fuzz));
            m_frame[1] = (tanh(m_frame[1] * m_fuzz) / tanh(m_fuzz));
            m_frame[0] /= 100;
            m_frame[1] /= 100;
        }

        m_frame[0] = m_effects.Generate(m_frame)[0];
        m_frame[1] = m_effects.Generate(m_frame)[1];

        oscillator -= (1 / m_sampleRate);
    }

    oscillator += GetSamplePeriod();
    // Update time
    m_time += GetSamplePeriod();
    // We return true until the time reaches the duration.
    if (m_time < m_duration == false) {
        m_wavein->Rewind();
    }
    return m_time < m_duration;
}

void CRecordingInstrument::SetNote(CNote* note)
{
    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for (int i = 0; i < len; i++)
    {
        // Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);

        // Get the value of the attribute.  A CComVariant is a variable
        // that can have any type. It loads the attribute value as a
        // string (UNICODE), but we can then change it to an integer 
        // (VT_I4) or double (VT_R8) using the ChangeType function 
        // and then read its integer or double value from a member variable.
        CComVariant value;
        attrib->get_nodeValue(&value);

        if (name == "duration")
        {
            value.ChangeType(VT_R8);
            SetDuration(value.dblVal * (1 / (m_bpm / 60)));
        }
        else if (name == "note")
        {
            SetFreq(NoteToFrequency(value.bstrVal));
        }
        else if (name == "sample")
        {
            fs::path filepath = fs::current_path();
            auto test = filepath.wstring() + value.bstrVal;
            CComVariant file = test.c_str();
            m_sampleRate = m_wavein->SampleRate();
            m_numChannels = m_wavein->NumChannels();
            m_numSampleFrames = m_wavein->NumSampleFrames();
        }
    }

}

void CRecordingInstrument::ProcessReadFrame(short* p_frame)
{
    m_wavein->ReadFrame(p_frame);
}
