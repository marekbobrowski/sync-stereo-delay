#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

class Processor : public Steinberg::Vst::AudioEffect
{
public:
	Processor ();
	~Processor () SMTG_OVERRIDE;

	static Steinberg::FUnknown* createInstance (void*) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new Processor; 
	}


	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;
	
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	Steinberg::tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
	
	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
		
	Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;
protected:
	float wet = 1;
	float delayBufferLeft[40000];
	float delayBufferRight[40000];
	float feedback = 0.5;
	unsigned delayRead = 0;
	unsigned delayWrite = 20000;
};

