# sync-stereo-delay

A VST3 delay plugin, whose main features are:
* feedback,
* stereo processing,
* synchronization with the host's tempo.

The processing algorithm was inspired by *Fruity Delay*'s ping-pong mode.


### Plugin showcase (turn on the audio)

https://user-images.githubusercontent.com/49000055/180647126-24088419-4cc5-4388-a0de-f76da3d88f88.mp4





## Setting up the project
This instruction has been prepared only for Windows and Visual Studio.
1. Download the [VST3 SDK](https://new.steinberg.net/developers/).
2. Open **CMakeLists.txt** and change the SDK path in the 4th line.
3. Run **Setup.bat**. This will generate Visual Studio project files in **build** folder.
4. Run Visual Studio either as administrator or enable symlinks before launching it with normal user permissions. The symlinks are needed, so after compilation the plugin will be instantly visible from the official VST3 directory. This will enable your DAW to see it. Otherwise you will get errors when compiling.
5. Load **build\sync-stereo-delay.sln**.
6. Build the solution :).
7. If the build succeeded (which requires symlinks enabled or Visual Studio ran as administrator), the plugin should be visible to your DAW.

### Debugging






