#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

#define MAX_DELAY_BUFFER_SIZE 441000 // 10 times regular sample rate = max 10 seconds delay

class Processor : public Steinberg::Vst::AudioEffect
{
public:
	Processor ();

	static Steinberg::FUnknown* createInstance (void*) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new Processor; 
	}

	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
		
protected:

	float wet;
	float feedback;
	unsigned delayRead;
	unsigned delayWrite;

	float* delayBufferLeft;
	float* delayBufferRight;
};

