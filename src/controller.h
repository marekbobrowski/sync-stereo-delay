#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"

class Controller : public Steinberg::Vst::EditControllerEx1
{
public:
	Controller () = default;

	static Steinberg::FUnknown* createInstance (void*)
	{
		return (Steinberg::Vst::IEditController*)new Controller;
	}

	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;

	DEFINE_INTERFACES
	END_DEFINE_INTERFACES (EditController)
    DELEGATE_REFCOUNT (EditController)
};

