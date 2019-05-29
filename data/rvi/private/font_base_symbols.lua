define("*",
[[
    draw_line(vec2(0.0,0.5), vec2(1.0,0.5));
    draw_line(vec2(0.0,1.0), vec2(1.0,0.0));
    draw_line(vec2(0.0,0.0), vec2(1.0,1.0));
]]);

define("-",
[[
    draw_line(vec2(0.0,0.5), vec2(1.0,0.5));
]]);

define("_",
[[
    draw_line(vec2(0.0,0.0), vec2(1.0,0.0));
]]);

define("+",
[[
    draw_line(vec2(0.0,0.5), vec2(1.0,0.5));
    draw_line(vec2(0.5,1.0), vec2(0.5,0.0));
]]);

define("/",
[[
    draw_line(vec2(0.0,0.0), vec2(1.0,1.0));
]]);

define("\\",
[[
    draw_line(vec2(0.0,1.0), vec2(1.0,0.0));
]]);

define("=",
[[
    draw_line(vec2(0.0,0.3), vec2(1.0,0.3));
    draw_line(vec2(0.0,0.7), vec2(1.0,0.7));
]]);

define("(",
[[
    draw_line(vec2(0.7,1.0), vec2(0.5,0.8));
    draw_line(vec2(0.5,0.8), vec2(0.5,0.2));
    draw_line(vec2(0.5,0.2), vec2(0.7,0.0));
]]);

define(")",
[[
    draw_line(vec2(0.3,1.0), vec2(0.5,0.8));
    draw_line(vec2(0.5,0.8), vec2(0.5,0.2));
    draw_line(vec2(0.5,0.2), vec2(0.3,0.0));
]]);

define("[",
[[
    draw_line(vec2(0.5,1.0), vec2(0.5,0.0));
    draw_line(vec2(0.5,1.0), vec2(0.7,1.0));
    draw_line(vec2(0.5,0.0), vec2(0.7,0.0));
]]);

define("]",
[[
    draw_line(vec2(0.5,1.0), vec2(0.5,0.0));
    draw_line(vec2(0.5,1.0), vec2(0.3,1.0));
    draw_line(vec2(0.5,0.0), vec2(0.3,0.0));
]]);

define("'",
[[
    draw_line(vec2(0.5,1.0), vec2(0.5,0.6));
]]);

define("#",
[[
    draw_line(vec2(0.25,1.0), vec2(0.25,0.0));
    draw_line(vec2(0.75,1.0), vec2(0.75,0.0));
    draw_line(vec2(0.0,0.25), vec2(1.0,0.25));
    draw_line(vec2(0.0,0.75), vec2(1.0,0.75));
]]);

define(" ");

define(",",
[[
    draw_line(vec2(0.5,0.2), vec2(0.5,0.0));
    draw_line(vec2(0.5,0.0), vec2(0.3,0.0));
]]);

define(":",
[[
    draw_line(vec2(0.35,1.0), vec2(0.35,0.6));
    draw_line(vec2(0.65,1.0), vec2(0.65,0.6));
]]);

define("$",
[[
    draw_line(vec2(1.0,0.8), vec2(0.0,0.8));
    draw_line(vec2(0.0,0.8), vec2(0.0,0.5));
    draw_line(vec2(0.0,0.5), vec2(1.0,0.5));
    draw_line(vec2(1.0,0.5), vec2(1.0,0.2));
    draw_line(vec2(1.0,0.2), vec2(0.0,0.2));
    draw_line(vec2(0.5,1.0), vec2(0.5,0.0));
]]);

define("?",
[[
    draw_line(vec2(0.0,1.0), vec2(1.0,1.0));
    draw_line(vec2(1.0,1.0), vec2(1.0,0.5));
    draw_line(vec2(1.0,0.5), vec2(0.5,0.5));
    draw_line(vec2(0.5,0.5), vec2(0.5,0.2));
    draw_line(vec2(0.5, 0.15), vec2(0.5,0.05));
    draw_line(vec2(0.45, 0.10, vec2(0.55, 0.10));
]]);