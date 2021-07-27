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
		STR16("fdb"));

	return kResultOk;
}
