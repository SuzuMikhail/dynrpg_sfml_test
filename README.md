# dynrpg_sfml_test


A performance test about RPG::Image and sf::Sprite with sf::Texture

rpg_draw() and sf_draw() calls many functions to display a picture to test the performance. These functions alloc memory at first, and free the memories at end.

The test is running with [system_opengl](https://github.com/andrew-r-king/system_opengl) plugin. TestResult.jpg shows RPG::Image is faster than SFML at the first time. Btw, SFML ignored plugin's FX (Because SFML is drawing above the window)


## If you want to test again


1. Create a RPG Maker 2003 project
2. Patch RPG_RT.exe with dynrpg_patcher.exe
3. Copy this directory to DynPlugins in RM2K3 project directory.
4. Create a event, insert comments and type a comment: `@TestWin` (To call Test)
5. Copy RM2K3_RTP/System/system1.png to System in RM2K3 project directory.
6. Watch the console.


## Build from source

1. Extrace SFML-2.5.0-TDM-GCC-32.7z to C:\\SFML-2.5.0-TDM-GCC-32\\
2. The linker and search directories for SFML should be setup already.
3. Build.
4. If troubles occured, SFML Tutorial and DynRPG Tutorial may be helped.


## Disclaimer

I wrote these code for test performance, and I copied many code by others to achieve it. So I didn't have any copyright to these code.
