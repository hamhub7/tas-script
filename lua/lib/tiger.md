# tiger.lua Documentation

## Features

This script format is intended to eliminate repetition of lines and make setting stick positions earlier, as it removes the need for coordinates.

## Syntax

Each line can have 1 or more components, separated by spaces. Required parameters are bolded.

1. **The frame number**:  
   This is the number of frames to advance from last line before doing anything. On the first line of the script, use +.
2. ON:  
   Presses the keys inside the brackets. Separate keys with commas. They are not released until the processor encounters an OFF or RAW parameter that releases them, or the script ends.
3. OFF:
   Works the same as ON but releases keys inside.
4. RAW:
   Presses the keys inside the brackets and releases all other keys.
5. LSTICK:
   Sets the left stick to the included angle (0 meaning forward, increasing moving clockwise) and magnitude (0-32767). Syntax: `LSTICK{180,32767}`. The left stick will be set here until it is changed.
6. RSTICK:
   Works the exact same as LSTICK but for the right stick.

### Available buttons

A, B, X, Y, LSTICK, RSTICK, L, R, ZL, ZR, PLUS, MINUS, DLEFT, DUP, DRIGHT, DDOWN

## Example script

The following script, when run in Super Mario Odyssey, will do a roll cancel directed to the left.

```
+ RAW{KEY_B}
1 OFF{ALL}
4 RAW{KEY_ZL}
1 OFF{ALL}
34 RAW{KEY_ZL,KEY_Y}
1 OFF{ALL}
1 RAW{KEY_X,KEY_A} LSTICK{90,30000}
1 OFF{KEY_X}
3 ON{NONE}
```
