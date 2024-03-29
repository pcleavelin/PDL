extern crate pdl_sys;

use pdl_sys::*;

const WIDTH: usize = 1024;
const HEIGHT: usize = 768;

fn main() {
	if !pdl_init("My Rust Game", 128, 128, WIDTH as u32, HEIGHT as u32, 1)
	{
		panic!("Failed to initialize pdl!");
	}

	println!("Initialized PDL!");

	let mut bitmap: Box<[u32]> = vec![0;WIDTH*HEIGHT].into_boxed_slice();

	loop{
		if !pdl_do_window_messages() {
			println!("Window Messages returned false");
			break;
		}

		if pdl_get_key(Key::Escape as u8) > 0 {
			println!("Escape key pressed!");
			break;
		}

		for y in 0..HEIGHT {
			for x in 0..WIDTH {
				// Do some pixel magic
				bitmap[x + y * WIDTH] = (0xFF000000 | (x%256) | ((y%256) << 8)) as u32;
			}
		}

		pdl_blit_bitmap(&bitmap);
	}

	println!("Closing window!");

	pdl_close_window();
}