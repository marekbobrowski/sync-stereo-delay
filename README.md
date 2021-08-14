# sync-stereo-delay

A VST3 delay plugin, whose main features are:
* feedback,
* stereo processing,
* synchronization with the host's tempo.

The processing algorithm was inspired by *Fruity Delay*'s ping-pong mode.

## Setting up the project
This instruction has been prepared only for Windows and Visual Studio.
1. Download the [VST3 SDK](https://new.steinberg.net/developers/).
2. Open your source folder in Explorer and edit **CMakeLists.txt** by changing SDK path in the 4th line.
3. Run **Setup.bat**. This will generate Visual Studio project files in a new *build* folder.
4. Run Visual Studio either as administrator or enable symlinks before launching it in normal mode. The symlinks are needed so after compilation, the plugin will be instantly visible from the official VST3 directory. This will enable your DAW to see it. Otherwise you will get errors when compiling.
5. Done 😊.



