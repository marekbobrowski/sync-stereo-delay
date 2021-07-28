#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"
#include "vstgui/plugin-bindings/vst3editor.h"


class Controller : public Steinberg::Vst::EditControllerEx1
{
public:
	Controller () = default;

	static Steinberg::FUnknown* createInstance (void*)
	{
		return (Steinberg::Vst::IEditController*)new Controller;
	}

	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;

	Steinberg::IPlugView* PLUGIN_API createView(const char* name) SMTG_OVERRIDE;

	DEFINE_INTERFACES
	END_DEFINE_INTERFACES (EditController)
    DELEGATE_REFCOUNT (EditController)
};

