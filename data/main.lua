include("rvi/rvi_font.lua");
include("rvi/rvi_color.lua");

select_frame("test_a");
	set_position(0.10, 0.45);
	set_scale(0.75, 0.10);
	r_set_color(rvi_color["orange"]);
    
	box_border();
	r_set_color(rvi_color["l_blue"]);
	stitch_fill_rlt(20);
	set_clickable("hello_click");
release_frame();