#include "processor.h"
#include "controller.h"
#include "ids.h"

#include "public.sdk/source/main/pluginfactory.h"

#define stringPluginName "sync-stereo-delay"
#define DelayVST3Category "Fx"
#define pluginVersionString "0.0.0"

using namespace Steinberg::Vst;

BEGIN_FACTORY_DEF ("Marek Bobrowski", 
			       "https://github.com/marekbobrowski", 
			       "-")

	DEF_CLASS2 (INLINE_UID_FROM_FUID(kProcessorUID),
				PClassInfo::kManyInstances,	
				kVstAudioEffectClass,	
				stringPluginName,		
				Vst::kDistributable,	
				DelayVST3Category, 
				pluginVersionString,		
				kVstVersionString,		
				Processor::createInstance)	

	DEF_CLASS2 (INLINE_UID_FROM_FUID (kControllerUID),
				PClassInfo::kManyInstances, 
				kVstComponentControllerClass,
				stringPluginName "Controller",	
				0,						
				"",						
				pluginVersionString,		
				kVstVersionString,		
				Controller::createInstance)


END_FACTORY
