#include "controller.h"
#include "ids.h"

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
	parameters.addParameter(STR16("Time"), nullptr, 4, 0.5,
		Vst::ParameterInfo::kCanAutomate, Params::time_, 0,
		STR16("tempo"));
	parameters.addParameter(STR16("Dry"), nullptr, 0, .5,
		Vst::ParameterInfo::kCanAutomate, Params::dry, 0,
		STR16("dry"));
	parameters.addParameter(STR16("Wet"), nullptr, 0, 0.5,
		Vst::ParameterInfo::kCanAutomate, Params::wet, 0,
		STR16("wet"));
	parameters.addParameter(STR16("Width"), nullptr, 0, 0.5,
		Vst::ParameterInfo::kCanAutomate, Params::width, 0,
		STR16("width"));

	setKnobMode(Vst::KnobModes::kLinearMode);

	// initial program
	setParamNormalized(Params::dry, 1);
	setParamNormalized(Params::wet, 1);
	setParamNormalized(Params::feedback, 0.5);
	setParamNormalized(Params::time_, 0.5);
	setParamNormalized(Params::width, 0.5);

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
