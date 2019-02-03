include("rvi/rvi_font.lua");
include("rvi/rvi_color.lua");

select_frame("hello_world");

	set_position(0.10, 0.45);
	set_scale(0.75, 0.10);
	rset_color(rvi_color["pink"]);
    
    rprint("Hello Friend");
	
release_frame();