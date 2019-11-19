extern
{
	fn PDLShowWindow();
	fn PDLHideWindow();
	fn PDLResizeWindow(width: u32, height: u32);
	fn PDLCloseWindow();

	fn PDLDoWindowMessages() -> bool;
	fn PDLInit(title: *const u8, len: usize) -> bool;
}

pub fn pdl_show_window()
{
	unsafe
	{
		PDLShowWindow()
	}
}

pub fn pdl_hide_window()
{
	unsafe
	{
		PDLHideWindow()
	}
}

pub fn pdl_resize_window(width: u32, height: u32)
{
	unsafe
	{
		PDLResizeWindow(width, height)
	}
}

pub fn pdl_close_window()
{
	unsafe
	{
		PDLCloseWindow()
	}
}

pub fn pdl_do_window_messages() -> bool
{
	unsafe
	{
		PDLDoWindowMessages()
	}
}

pub fn pdl_init(title: &str) -> bool
{
	unsafe
	{
		PDLInit(title.as_ptr(), title.len())
	}
}
