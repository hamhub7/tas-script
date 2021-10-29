# tas-script
A modification of sys-script by Aly to run on Lua and be more TAS focused\
Find sys-script [here](https://github.com/s5bug/sys-script)

## Examples
Big thanks to Mars2030 and the entire SMO TAS community for their incredible work on the Super Mario Odyssey TASes! Here are a few examples of what our program is capable of\
[Cap Kingdom Full TAS](https://www.youtube.com/watch?v=oMI796qC6xs) (note that motion controls are accomplished by an ingame mod that maps motion to button presses)

## Support the Creators
Join our [Discord server](https://discord.gg/HSPrhX8)\
Support me on [Patreon](https://www.patreon.com/aaronhh) or [PayPal](https://www.paypal.me/aaronhamhub)\
Make a pull request!

## Keybinds
`=`: Add a virtual controller (The switch can only support 8 controllers maximum, going over this will crash.)  
`-`: Remove a virtual controller  
`Q`: Press `A` on the first virtual controller  
`W`: Press `L` and `R` on each controller, sequentially  
`F1-F12`: Run a script. By default, the program will run `script1.txt` if `F1` is pressed, `script2.txt` if `F2` is pressed, and so on. However, if more that 1 controller is attached, it will instead run multiplayer scripts. If `F1` is pressed, it will run `script1-1.txt` on the first controller, `script1-2.txt` on the second controller, and so on.

## Building from Source
1. [Set up the required libraries](https://switchbrew.org/wiki/Setting_up_Development_Environment)
2. In the newly installed MSYS2, navigate to the folder you'd like to build this project in, either by opening MSYS in that directory or using the `cd` command to navigate
3. `git clone https://github.com/hamhub7/tas-script.git` (You may need to install git with `pacman -S git`)
4. `cd tas-script`
5. `make lua` to build and install Lua (You may need to install make with `pacman -S make`)
\
\
TODO: `switch-lua` should be installable from `pacman`.
6. `make`
7. You should see a file called `tas-script.nsp`
\
\
Optionally, you can choose to run `make sd` to make a convenient sd card package. The command should create a folder called `sd` that you can simply drag and drop the contents of onto your sd card.

The `make` process will fail for one of three reasons:
- You cloned a commit that doesn't compile (unlikely)
- Your folder is named something other than `tas-script`; solution is to `ln -s tas-script.json config.json`
- Your directory's full path has spaces in it (usually your account name)
