include("rvi/rvi_font.lua");
include("rvi/rvi_color.lua");

select_frame("test_a");
	set_position(0.25, 0.25);
	set_scale(0.5, 0.5);
	r_set_color(rvi_color["orange"]);
    
	box_border();
	stitch_fill_rlt(10);
	distort(0, 0.5, 0, 0, 0, 0, 0, 0);
	set_clickable("hello_click");
release_frame();