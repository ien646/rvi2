include("rvi/rvi_font.lua");
include("rvi/rvi_color.lua");

select_frame("test_a");
	set_position(0.10, 0.45);
	set_scale(0.75, 0.10);
	rset_color(rvi_color["orange"]);
    
	rbox_border();
	rset_color(rvi_color["l_blue"]);
	rstitch_fill_rel(20);
	set_clickable("hello_click");
release_frame();