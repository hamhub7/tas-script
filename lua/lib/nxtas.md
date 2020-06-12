# nx-TAS Documentation
## Features
nx-TAS script formatting does not include any special features like macros, as it intended to be a rather basic format that anyone can use. nx-TAS format may get a reboot when motion controls are released, but the original legacy format will always be around for maximum compatibility.

## Syntax
Each line should have 4 components, separated by spaces.
1. The frame number:  
This is the absolute number of frames since the script is started, meaning that all frame numbers will need to be in numerical order
2. The keys to be pressed:  
The keys available to be pressed can be found below. You may have as many keys pressed on a current frame as you like, but they must be separated by semicolons. The script has no memory, and does not remember what keys were pressed on previous frames. Each line is the absolute keys pressed.
3. The left joystick:
The left joystick is in cartesian coordinates, so first the x value must be specified, then the y value. These two values should be separated by a semicolon and can range from -32767 to 32767. However, there is a deadzone in each corner, essentially making the active area a circle of radius 32767 around the center of the joystick. As long as the joysticks stay in this radius, the script should be able to set them with no difficulty.
4. The right joystick:
The right stick follows the same syntax and deadzone as the left joystick.  

### Available buttons
KEY_A, KEY_B, KEY_X, KEY_Y, KEY_LSTICK, KEY_RSTICK, KEY_L, KEY_R, KEY_ZL, KEY_ZR, KEY_PLUS, KEY_MINUS, KEY_DLEFT, KEY_DUP, KEY_DRIGHT, KEY_DDOWN

## Example script
The following script, when run in Super Mario Odyssey, will do a roll cancel directed to the left.
```
1 KEY_B 0;0 0;0
6 KEY_ZL 0;0 0;0
41 KEY_ZL;KEY_Y 0;0 0;0
43 KEY_X;KEY_A 30000;0 0;0
44 KEY_A 30000;0 0;0
45 KEY_A 30000;0 0;0
46 KEY_A 30000;0 0;0
47 KEY_A 30000;0 0;0
```