# Library Documentation Guide
This guide will explain how to properly create a pull request with your tas library and the correct formatting it should use  

## Making a Pull Request
To make a pull request properly, follow these steps:
1. Click the `Fork` button at the top
2. Add your `.lua` library file and your `.md` documentation file to the `/lua/lib` folder in your fork
3. Go to your fork's GitHub page and clcik the `New Pull Request` button right above your file listing
4. Click the green `Create Pull Request` button
5. Change the title to `New Library: libray.lua`, using the name of your library
6. Leave any necessary comments, then click `Create Pull Request`
7. That's it! Your library should be added soon

## Library Formatting
There are a couple general rules and conventions for making a lua library that fits with the program
1. In your lua file, make sure to create an empty table at the top with the same name as your file, then return it at the end. For example, in `nxtas.lua`, we have `local nxtas = {}` at the top and `return nxtas` at the bottom
2. Set your file extension with `libname.fileext`. In `nxtas.lua`, we have `nxtas.fileext = "txt"`. Do NOT include the dot (`txt` vs `.txt`)
3. If your library has multiplayer support, set `libname.multiplayer = true`. Otherwise, set it to false
4. The functions included in your library do not matter, but there are some required ones. The required functions should be defined with `libname.functionname` instead of just `functionname`. For example, nxtas implements the `runTas` function with the syntax `function nxtas.runTas(filename, controller) ... end`
5. Any functions other than these required ones should NOT be included in your library's table. You can simply define a function normally (without the `libname.`) to omit it from your table
6. All libraries must implement `libname.runTas(filename, controller)`. This function is the main way to run a TAS, and should use the filename to set the inputs on the controller provided (note that the filename is the absolute path). An example implementation can be found [here](https://github.com/hamhub7/tas-script/blob/master/lua/lib/nxtas.lua#L91)
7. If your library implements multiplayer, you must implement `libname.runMulitplayerTas(filenames, controllers)`. This function should run multiple simultaneous TASes, with the filenames provided in an array/table to be run on the controllers, also provided in an array/table. The indices of both arrays should correspond, so `filename[1]` should be run on `controller[1]`. If you set `libname.multiplayer = false`, you do not have to implement this function

## Documentation
Each library should be accompanied by a `libname.md` file to describe how the syntax of the format works. Some detailed information about how the script format works, and possibly some examples, are enough. If need be, I can respond to a pull request with a request to add more detailed documentation if it seems lacking. A example doc can be found [here](https://github.com/hamhub7/tas-script/tree/master/lua/lib)  
### Basic Guidelines
Tell the user:
* what syntax is used to represent each key
* what system is used to represent joystick position
* how to set both the joysticks and buttons
* how to determine what frame the inputs shoud be extecuted on
* how to define macros (if your script supports them)
* about any other unique features your script format has

## Help
If you need a starting point for your library, check out `nxtas.lua` and `tiger.lua`. nxtas uses absolute frame numbers and tiger uses frame delays, so if you want to base your library off either one of those systems, you can simply change the `scanLine` function
For help coding in lua, check out [Programming in Lua](https://www.lua.org/pil/contents.html) or the [Lua Documentation](https://www.lua.org/manual/5.3/)
