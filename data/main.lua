include("rvi/font.lua");
include("rvi/color.lua");
include("rvi/text_format.lua")

select_frame("test_a");
	set_position(vec2(0.25, 0.25));
	set_scale(vec2(0.5, 0.5));
	r_set_color("orange");
	box_border();

	printr_wrap("Hi there friend");
	set_cursive();
release_frame();