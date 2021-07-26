#include "controller.h"

using namespace Steinberg;

tresult PLUGIN_API Controller::initialize (FUnknown* context)
{

	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	return result;
}

tresult PLUGIN_API Controller::terminate ()
{
	return EditControllerEx1::terminate ();
}

tresult PLUGIN_API Controller::setComponentState (IBStream* state)
{
	if (!state)
		return kResultFalse;

	return kResultOk;
}

tresult PLUGIN_API Controller::setState (IBStream* state)
{
	return kResultTrue;
}

tresult PLUGIN_API Controller::getState (IBStream* state)
{
	return kResultTrue;
}

IPlugView* PLUGIN_API Controller::createView (FIDString name)
{
	return nullptr;
}

tresult PLUGIN_API Controller::setParamNormalized (Vst::ParamID tag, Vst::ParamValue value)
{
	tresult result = EditControllerEx1::setParamNormalized (tag, value);
	return result;
}

tresult PLUGIN_API Controller::getParamStringByValue (Vst::ParamID tag, Vst::ParamValue valueNormalized, Vst::String128 string)
{
	return EditControllerEx1::getParamStringByValue (tag, valueNormalized, string);
}

tresult PLUGIN_API Controller::getParamValueByString (Vst::ParamID tag, Vst::TChar* string, Vst::ParamValue& valueNormalized)
{
	return EditControllerEx1::getParamValueByString (tag, string, valueNormalized);
}

