if rvi == nil then
    rvi = {}
end

rvi.color_list = {
    black   = { 0,    0,    0,    255 },
    gray    = { 127,  127,  127,  255 },
    grey    = { 127,  127,  127,  255 },
    white   = { 255,  255,  255,  255 },
    red     = { 255,  0,    0,    255 },
    green   = { 0,    255,  0,    255 },
    blue    = { 0,    0,    255,  255 },
    l_blue  = { 127,  127,  255,  255 },
    yellow  = { 255,  255,  0,    255 },
    magenta = { 255,  0,    255,  255 },
    fuchsia = { 255,  127,  255,  255 },
    orange  = { 255,  127,  0,    255 },
    brown   = { 170,  119,  54,   255 },
    pink    = { 255,  100,  200,  255 }
};

rvi.set_color = function (name)
    entry = rvi.color_list[name];
    set_color(color_rgba.new(entry[1], entry[2], entry[3], entry[4]))
end