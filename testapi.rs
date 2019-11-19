extern crate pdl_sys;

use pdl_sys::*;

fn main() {
	pdl_init();

	pdl_resize_window(1024, 768);

	loop{
		if !pdl_do_window_messages() {
			break;
		}
	}
}