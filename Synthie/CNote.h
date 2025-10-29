#pragma once
#include "string"
#include "map"
#include "audio/DirSoundSource.h"
class CNote
{
public:
    CNote(void);
    virtual ~CNote(void);

    int Measure() const { return m_measure; }
    double Beat() const { return m_beat; }
    double Fuzz() const { return m_fuzz_intensity; }
    const std::wstring& Instrument() const { return m_instrument; }
    CDirSoundSource* SoundRecording() { return m_soundRecording; }
    IXMLDOMNode* Node() { return m_node; }
    void XmlLoad(IXMLDOMNode* xml, std::wstring& instrument);
    bool operator<(const CNote& b);

private:
    std::wstring m_instrument;
    int m_measure;
    double m_beat;
    CDirSoundSource* m_soundRecording;
    CComPtr<IXMLDOMNode> m_node;
    double m_fuzz_intensity;
};

