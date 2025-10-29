#pragma once
#include "CAudioNode.h"
#include "CNote.h"
#include "CEffects.h"
class CInstrument :
    public CAudioNode
{
public:
	CInstrument(void);
	virtual ~CInstrument(void);
	virtual void SetNote(CNote* note) = 0;
	void SetBPM(double d) { m_bpm = d; }
	virtual void SetSoundSource(CDirSoundSource* source) {}
	virtual void SetFuzz(double f) {}
	virtual void SetEffects(CEffects e) {}
};

