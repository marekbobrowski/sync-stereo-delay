#include "controller.h"
#include "ids.h"
#include "base/source/fstreamer.h"

using namespace Steinberg;

tresult PLUGIN_API Controller::initialize (FUnknown* context)
{
	tresult result = EditControllerEx1::initialize (context);

	if (result != kResultOk)
	{
		return result;
	}
	parameters.addParameter(STR16("Feedback"), nullptr, 0, .5,
		Vst::ParameterInfo::kCanAutomate, Params::feedback, 0,
		STR16("feedback"));
	parameters.addParameter(STR16("Dry"), nullptr, 0, .5,
		Vst::ParameterInfo::kCanAutomate, Params::dry, 0,
		STR16("dry"));
	parameters.addParameter(STR16("Wet"), nullptr, 0, 0.5,
		Vst::ParameterInfo::kCanAutomate, Params::wet, 0,
		STR16("wet"));
	parameters.addParameter(STR16("Width"), nullptr, 0, 0.5,
		Vst::ParameterInfo::kCanAutomate, Params::width, 0,
		STR16("width"));
	parameters.addParameter(STR16("DelayTime"), nullptr, 8, 0,
		Vst::ParameterInfo::kCanAutomate, Params::delayTime, 0,
		STR16("DelayTime"));

	setKnobMode(Vst::KnobModes::kLinearMode);

	return kResultOk;
}

Steinberg::IPlugView* PLUGIN_API Controller::createView(const char* name)
{
	if (name && strcmp(name, "editor") == 0)
	{
		auto* view = new VSTGUI::VST3Editor(this, "view", ".uidesc");
		return view;
	}
	return nullptr;
}


tresult PLUGIN_API Controller::setComponentState(IBStream* state)
{
	// we receive the current state of the component (processor part)

	if (!state)
		return kResultFalse;

	IBStreamer streamer(state, kLittleEndian);

	// read the dry value
	float dry = 0;
	if (streamer.readFloat(dry) == false)
		return kResultFalse;
	setParamNormalized(Params::dry, dry);
	
	float wet = 0;
	// read the wet value
	if (streamer.readFloat(wet) == false)
		return kResultFalse;
	setParamNormalized(Params::wet, wet);

	float feedback = 0;
	// read the feedback value
	if (streamer.readFloat(feedback) == false)
		return kResultFalse;
	setParamNormalized(Params::feedback, feedback);

	float width = 0;
	// read the width value
	if (streamer.readFloat(width) == false)
		return kResultFalse;
	setParamNormalized(Params::width, width);

	float time = 0;
	// read the time value
	if (streamer.readFloat(time) == false)
		return kResultFalse;
	time = time * 2 - 0.125;
	setParamNormalized(Params::delayTime, time);

	

	return kResultOk;
}
