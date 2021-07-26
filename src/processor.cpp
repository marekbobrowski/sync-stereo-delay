#include "processor.h"
#include "ids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

using namespace Steinberg;

Processor::Processor ()
{
	setControllerClass (kControllerUID);
}


Processor::~Processor ()
{}


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


tresult PLUGIN_API Processor::terminate ()
{
	return AudioEffect::terminate ();
}


tresult PLUGIN_API Processor::setActive (TBool state)
{
	return AudioEffect::setActive (state);
}


tresult PLUGIN_API Processor::process (Vst::ProcessData& data)
{
	return kResultOk;
}


tresult PLUGIN_API Processor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	return AudioEffect::setupProcessing (newSetup);
}


tresult PLUGIN_API Processor::canProcessSampleSize (int32 symbolicSampleSize)
{
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;
	return kResultFalse;
}


tresult PLUGIN_API Processor::setState (IBStream* state)
{
	IBStreamer streamer (state, kLittleEndian);
	return kResultOk;
}


tresult PLUGIN_API Processor::getState (IBStream* state)
{
	IBStreamer streamer (state, kLittleEndian);
	return kResultOk;
}

