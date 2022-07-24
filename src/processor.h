#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

#define MAX_DELAY_BUFFER_SIZE 441000 // 10 times regular sample rate = max 10 seconds divided by 2

class Processor : public Steinberg::Vst::AudioEffect
{
public:
	Processor ();

	static Steinberg::FUnknown* createInstance (void*) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new Processor; 
	}

	// OVERRIDE DEFAULT VST PROCESSOR METHODS

	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;

	/**
	 * Sets the samplesDelay variable and creates an offset between "write" and "read" positions in the delay buffer.
	 */
	void setDelay(unsigned nSamples);

	/**
	 * Updates local tempo variable if it has changed in the host.
	 * 
	 * \returns True if the tempo has changed.
	 */
	bool updateTempo(Steinberg::Vst::ProcessData& data);

	/**
	 * Calculates current delay in samples based on "time" parameter and host's tempo.
	 * 
	 * \returns The calculated delay.
	 */
	unsigned calculateDelay();

	/**
	 * Handles any changes of plugin parameters.
	 */
	void handleParameterChange(Steinberg::Vst::ProcessData& data);

	/**
	 * Calculates and sets delay based on internal parameters.
	 */
	void calcSetDelay();

	/**
	 * Processes the sound signal buffer.
	 */
	void processBuffer(void** in, void** out, Steinberg::int32 numSamples);

	/**
	 * Handles the silence flags.
	 */
	void handleSilenceFlags(void** in, void** out, Steinberg::Vst::ProcessData& data);
		
protected:

	float dry;
	float wet;
	float feedback;
	float width;
	float time;

	double tempo;

	unsigned delayRead;
	unsigned delayWrite;
	unsigned samplesDelay;

	float* delayBufferLeft;
	float* delayBufferRight;
};

