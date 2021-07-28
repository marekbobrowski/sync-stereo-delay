cmake_minimum_required(VERSION 3.14.0)
project(sync-stereo-delay)

set(vst3sdk_SOURCE_DIR D:/Programming/SDKs/VST_SDK/VST3_SDK)
add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
  
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(sync-stereo-delay     
    src/ids.h
    src/processor.h
    src/processor.cpp
    src/controller.h
    src/controller.cpp
    src/entry.cpp
)

target_link_libraries(sync-stereo-delay
	PRIVATE
		sdk
        vstgui_support
)

smtg_add_vst3_resource(sync-stereo-delay "gui/.uidesc")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sync-stereo-delay)

