#pragma once
class CEffects
{
public:
	CEffects(void);
	virtual ~CEffects(void);

	virtual double* Generate(double* m_frame);
};

