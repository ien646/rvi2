rvi_color = {
	black 	= { 0, 		0, 		0, 		255 },
	gray	= { 127,	127,	127, 	255 },
	grey	= { 127,	127,	127, 	255 },
	white 	= { 255,  	255, 	255, 	255 },
	red		= { 255, 	0,		0,		255 },
	green	= { 0,		255,	0,		255 },
	blue	= { 0,		0,		255,	255 },
	l_blue  = { 127,	127,	255,	255 },
	yellow	= { 255,	255,	0,		255 },
	magenta = { 255,	0,		255,	255 },
	fuchsia	= { 255,	127,	255,	255 },
	orange 	= { 255,	127,	0,		255 },
	brown	= { 170, 	119, 	54,		255 },
	pink	= { 255,	100,	200,	255 }
};

function r_set_color(color)
	set_color(color[1], color[2], color[3], color[4]);
end