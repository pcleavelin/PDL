extern crate pdl_sys;

use pdl_sys::*;

const WIDTH: usize = 1024;
const HEIGHT: usize = 768;

fn main() {
	if !pdl_init("My Rust Game")
	{
		panic!("Failed to initialize pdl!");
	}

	pdl_resize_window(WIDTH as u32, HEIGHT as u32);

	let mut bitmap: Box<[u32]> = vec![0;WIDTH*HEIGHT].into_boxed_slice();

	loop{
		if !pdl_do_window_messages() {
			break;
		}

		for y in 0..HEIGHT {
			for x in 0..WIDTH {
				if y == HEIGHT-1 || y == 0
				{
					bitmap[x + y * WIDTH] = 0xFF88FF88;
				}

				if x == y
				{
					bitmap[x + y * WIDTH] = 0xFF880088;
				}
			}
		}

		pdl_blit_bitmap(&bitmap);
	}
}