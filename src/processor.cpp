#include "processor.h"
#include "ids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h";

using namespace Steinberg;

Processor::Processor ()
{
	setControllerClass (kControllerUID);
}

tresult PLUGIN_API Processor::initialize (FUnknown* context)
{
	tresult result = AudioEffect::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

tresult PLUGIN_API Processor::setActive (TBool state)
{
	if (state)
	{
		memset(delayBufferLeft, 0, 40000 * sizeof(float));
		memset(delayBufferRight, 0, 40000 * sizeof(float));
	}
	else 
	{
	}
	return AudioEffect::setActive (state);
}


tresult PLUGIN_API Processor::process (Vst::ProcessData& data)
{
	if (data.numInputs == 0 || data.numOutputs == 0)
	{
		return kResultOk;
	}

	void** in = getChannelBuffersPointer(processSetup, *data.inputs);
	void** out = getChannelBuffersPointer(processSetup, *data.outputs);

	int32 numChannels = data.inputs[0].numChannels;
	uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);

	if (data.inputs[0].silenceFlags != 0)
	{
		data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;

		for (int32 i = 0; i < numChannels; i++)
		{
			if (in[i] != out[i])
			{
				memset(out[i], 0, sampleFramesSize);
			}
		}
		return kResultOk;
	}

	if (data.numSamples > 0)
	{
		float* inRight = (float*)in[0];
		float *outRight = (float*)out[0];
		float* inLeft = (float*)in[1];
		float* outLeft = (float*)out[1];
		for (int i = 0; i < data.numSamples; i++)
		{
			outLeft[i] = inLeft[i] + wet * delayBufferLeft[delayRead];
			outRight[i] = inRight[i] + wet * delayBufferRight[delayRead];
			delayBufferLeft[delayWrite] = (inLeft[i] + inRight[i]) / 2 + delayBufferRight[delayRead] * feedback;
			delayBufferRight[delayWrite] = delayBufferLeft[delayRead] * feedback;
			delayWrite = (delayWrite + 1) % 40000;
			delayRead = (delayRead + 1) % 40000;
		}
	}
	return kResultOk;
}


tresult PLUGIN_API Processor::canProcessSampleSize (int32 symbolicSampleSize)
{
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;
	return kResultFalse;
}