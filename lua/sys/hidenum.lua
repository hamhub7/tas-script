hidenum = {}

hidenum.MouseButton = {
    Left = 1 << 0,
    Right = 1 << 1,
    Middle = 1 << 2,
    Forward = 1 << 3,
    Back = 1 << 4
}

hidenum.KeyboardModifier = {
    LCtrl = 1 << 0,
    LShift = 1 << 1,
    LAlt = 1 << 2,
    RAlt = 1 << 3,
    Gui = 1 << 4,
    CapsLock = 1 << 8,
    ScrollLock = 1 << 9,
    NumLock = 1 << 10,
    Katakan = 1 << 11,
    Hiragana = 1 << 12
}

hidenum.KeyboardKey = {
    A                = 4,
    B                = 5,
    C                = 6,
    D                = 7,
    E                = 8,
    F                = 9,
    G                = 10,
    H                = 11,
    I                = 12,
    J                = 13,
    K                = 14,
    L                = 15,
    M                = 16,
    N                = 17,
    O                = 18,
    P                = 19,
    Q                = 20,
    R                = 21,
    S                = 22,
    T                = 23,
    U                = 24,
    V                = 25,
    W                = 26,
    X                = 27,
    Y                = 28,
    Z                = 29,

    D1               = 30,
    D2               = 31,
    D3               = 32,
    D4               = 33,
    D5               = 34,
    D6               = 35,
    D7               = 36,
    D8               = 37,
    D9               = 38,
    D0               = 39,

    Return           = 40,
    Escape           = 41,
    Backspace        = 42,
    Tab              = 43,
    Space            = 44,
    Minus            = 45,
    Plus             = 46,
    OpenBracket      = 47,
    CloseBracket     = 48,
    Pipe             = 49,
    Tilde            = 50,
    Semicolon        = 51,
    Quote            = 52,
    Backquote        = 53,
    Comma            = 54,
    Period           = 55,
    Slash            = 56,
    CapsLock         = 57,

    F1               = 58,
    F2               = 59,
    F3               = 60,
    F4               = 61,
    F5               = 62,
    F6               = 63,
    F7               = 64,
    F8               = 65,
    F9               = 66,
    F10              = 67,
    F11              = 68,
    F12              = 69,

    PrintScreen      = 70,
    ScrollLock       = 71,
    Pause            = 72,
    Insert           = 73,
    Home             = 74,
    PageUp           = 75,
    Delete           = 76,
    End              = 77,
    PageDown         = 78,
    RightArrow       = 79,
    LeftArrow        = 80,
    DownArrow        = 81,
    UpArrow          = 82,

    NumLock          = 83,
    NumPadDivide     = 84,
    NumPadMultiply   = 85,
    NumPadSubtract   = 86,
    NumPadAdd        = 87,
    NumPadEnter      = 88,
    NumPad1          = 89,
    NumPad2          = 90,
    NumPad3          = 91,
    NumPad4          = 92,
    NumPad5          = 93,
    NumPad6          = 94,
    NumPad7          = 95,
    NumPad8          = 96,
    NumPad9          = 97,
    NumPad0          = 98,
    NumPadDot        = 99,
    Backslash        = 100,
    Application      = 101,
    Power            = 102,
    NumPadEquals     = 103,

    F13              = 104,
    F14              = 105,
    F15              = 106,
    F16              = 107,
    F17              = 108,
    F18              = 109,
    F19              = 110,
    F20              = 111,
    F21              = 112,
    F22              = 113,
    F23              = 114,
    F24              = 115,

    NumPadComma      = 133,

    Ro               = 135,
    KatakanaHiragana = 136,
    Yen              = 137,
    Henkan           = 138,
    Muhenkan         = 139,
    NumPadCommaPc98  = 140,
    HangulEnglish    = 144,
    Hanja            = 145,
    Katakana         = 146,
    Hiragana         = 147,
    ZenkakuHankaku   = 148,
    
    LeftControl      = 224,
    LeftShift        = 225,
    LeftAlt          = 226,
    LeftGui          = 227,
    RightControl     = 228,
    RightShift       = 229,
    RightAlt         = 230,
    RightGui         = 231
}

hidenum.ControllerType = {
    ProController = 1 << 0,
    Handheld = 1 << 1,
    JoyconPair = 1 << 2,
    JoyconLeft = 1 << 3,
    JoyconRight = 1 << 4,
    SystemExt = 1 << 29,
    System = 1 << 30
}

hidenum.ControllerLayoutType = {
    ProController = 0,
    Handheld = 1,
    Single = 2,
    Left = 3,
    Right = 4,
    DefaultDigital = 5,
    Default = 6
}

hidenum.ControllerKeys = {
    A       = 1 << 0,
    B       = 1 << 1,
    X       = 1 << 2,
    Y       = 1 << 3,
    LSTICK  = 1 << 4,
    RSTICK  = 1 << 5,
    L       = 1 << 6,
    R       = 1 << 7,
    ZL      = 1 << 8,
    ZR      = 1 << 9,
    PLUS    = 1 << 10,
    MINUS   = 1 << 11,
    DLEFT   = 1 << 12,
    DUP     = 1 << 13,
    DRIGHT  = 1 << 14,
    DDOWN   = 1 << 15,
    LSTICK_LEFT = 1 << 16,
    LSTICK_UP = 1 << 17,
    LSTICK_RIGHT = 1 << 18,
    LSTICK_DOWN = 1 << 19,
    RSTICK_LEFT = 1 << 20,
    RSTICK_UP = 1 << 21,
    RSTICK_RIGHT = 1 << 22,
    RSTICK_DOWN = 1 << 23,
    SL_LEFT = 1 << 24,
    SR_LEFT = 1 << 25,
    SL_RIGHT = 1 << 26,
    SR_RIGHT = 1 << 27,

    HOME = 1 << 18,
    CAPTURE = 1 << 19,

    TOUCH = 1 << 28,

    JOYCON_RIGHT = 1 << 0,
    JOYCON_DOWN = 1 << 1,
    JOYCON_UP = 1 << 2,
    JOYCON_LEFT = 1 << 3,

    UP = (1 << 13) | (1 << 17) | (1 << 21),
    DOWN = (1 << 15) | (1 << 19) | (1 << 23),
    LEFT = (1 << 12) | (1 << 16) | (1 << 20),
    RIGHT = (1 << 14) | (1 << 18) | (1 << 22),
    SL = (1 << 24) | (1 << 26),
    SR = (1 << 25) | (1 << 27)
}

hidenum.ControllerJoystick = {
    Left = 0,
    Right = 1,
    NumSticks = 2
}

hidenum.ControllerConnectionState = {
    Connected = 1 << 0,
    Wired = 1 << 1
}

hidenum.ControllerID = {
    Player1 = 0,
    Player2 = 1,
    Player3 = 2,
    Player4 = 3,
    Player5 = 4,
    Player6 = 5,
    Player7 = 6,
    Player8 = 7,
    Handheld = 8,
    Unknown = 9,
    P1Auto = 10
}

hidenum.InterfaceType = {
    Bluetooth = 1,
    Rail = 2,
    USB = 3,
    Unknown = 4
}

return hidenum