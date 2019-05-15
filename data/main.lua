include("rvi/font.lua");
include("rvi/color.lua");
include("rvi/text_format.lua")

sfptr = 0;

function fff()
	select_frame("test_a");
		clear_children();
	release_frame();
end

select_frame("test_a");
	sfptr = get_selected_frame_ptr();
	set_position(vec2(0.25, 0.25));
	set_scale(vec2(0.5, 0.5));
	r_set_color("orange");	

	printr_wrap("Hi there friend");
	set_clickable("ttt");
	add_click_handler("fff");
release_frame();

select_frame_by_ptr(sfptr);	
	printv(sfptr);
release_frame();