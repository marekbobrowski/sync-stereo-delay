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
	parameters.addParameter(STR16("Tempo"), nullptr, 0, 0.5,
		Vst::ParameterInfo::kCanAutomate, Params::tempo, 0,
		STR16("tempo"));

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
