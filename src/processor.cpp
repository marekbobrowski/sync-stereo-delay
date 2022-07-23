#include "processor.h"
#include "ids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h";
#include "pluginterfaces/vst/ivstprocesscontext.h"

using namespace Steinberg;

Processor::Processor()
	: dry(1),
	wet(1),
	feedback(.5),
	width(.5),
	delayRead(0),
	tempo(0),
	time(0.25),
	delayBufferLeft(nullptr),
	delayBufferRight(nullptr)
{
	setControllerClass (kControllerUID);
	samplesDelay = MAX_DELAY_BUFFER_SIZE;
	delayWrite = samplesDelay;
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
		delayBufferLeft = new float[MAX_DELAY_BUFFER_SIZE];
		delayBufferRight = new float[MAX_DELAY_BUFFER_SIZE];
		memset(delayBufferLeft, 0, MAX_DELAY_BUFFER_SIZE * sizeof(float));
		memset(delayBufferRight, 0, MAX_DELAY_BUFFER_SIZE * sizeof(float));
	}
	else 
	{
		delete[] delayBufferLeft;
		delete[] delayBufferRight;
		delayBufferLeft = nullptr;
		delayBufferRight = nullptr;
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

	if (data.inputs[0].silenceFlags != 0)
	{
		handleSilenceFlags(in, out, data);
		return kResultOk;
	}

	handleParameterChange(data);

	if (updateTempo(data))
	{
		calcSetDelay();
	}

	if (data.numSamples > 0)
	{
		processBuffer(in, out, data.numSamples);
	}
	return kResultOk;
}


tresult PLUGIN_API Processor::canProcessSampleSize (int32 symbolicSampleSize)
{
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;
	return kResultFalse;
}

void Processor::setDelay(unsigned nSamples)
{
	int temp = delayWrite - nSamples;

	while (temp < 0)
	{
		temp += MAX_DELAY_BUFFER_SIZE;
	}

	delayRead = temp;
}

bool Processor::updateTempo(Vst::ProcessData& data)
{

	if (data.processContext && data.processContext->state & Vst::ProcessContext::kTempoValid)
	{
		if (data.processContext->tempo != tempo)
		{
			tempo = data.processContext->tempo;
			return true;
		}
	}
	return false;
}

unsigned Processor::calculateDelay()
{
	return (60. / tempo) * time * 4 * processSetup.sampleRate;
}

void Processor::handleParameterChange(Vst::ProcessData& data)
{
	// Read inputs parameter changes
	if (data.inputParameterChanges)
	{
		int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
		for (int32 index = 0; index < numParamsChanged; index++)
		{
			Vst::IParamValueQueue* paramQueue =
				data.inputParameterChanges->getParameterData(index);
			if (paramQueue)
			{
				Vst::ParamValue value;
				int32 sampleOffset;
				int32 numPoints = paramQueue->getPointCount();
				switch (paramQueue->getParameterId())
				{
				case Params::feedback:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						feedback = value;
					}
					break;
				case Params::time_:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						time = value;
						calcSetDelay();
					}
					break;
				case Params::dry:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						dry = value;
					}
					break;
				case Params::wet:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						wet = value;
					}
					break;
				case Params::width:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						width = value;
					}
					break;
				}

			}
		}
	}
}

void Processor::calcSetDelay()
{
	setDelay(calculateDelay());
}


void Processor::handleSilenceFlags(void** in, void** out, Vst::ProcessData& data)
{
	uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
	data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;

	for (int32 i = 0; i < data.inputs[0].numChannels; i++)
	{
		if (in[i] != out[i])
		{
			memset(out[i], 0, sampleFramesSize);
		}
	}
}

void Processor::processBuffer(void** in, void** out, int32 numSamples)
{

	float* inRight = (float*)in[0];
	float* outRight = (float*)out[0];
	float* inLeft = (float*)in[1];
	float* outLeft = (float*)out[1];
	float mixed = 0;

	for (int i = 0; i < numSamples; i++)
	{
		outLeft[i] = dry * inLeft[i] + wet * delayBufferLeft[delayRead];
		outRight[i] = dry * inRight[i] + wet * delayBufferRight[delayRead];
		mixed = (inLeft[i] + inRight[i]) / 2;
		delayBufferLeft[delayWrite] = (1 - width) * mixed + delayBufferRight[delayRead] * feedback;
		delayBufferRight[delayWrite] = width * mixed + delayBufferLeft[delayRead] * feedback;
		delayWrite = (delayWrite + 1) % MAX_DELAY_BUFFER_SIZE;
		delayRead = (delayRead + 1) % MAX_DELAY_BUFFER_SIZE;
	}
}
