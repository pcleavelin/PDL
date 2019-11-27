extern "C" {
    fn PDLShowWindow();
    fn PDLHideWindow();
    fn PDLResizeWindow(width: u32, height: u32);
    fn PDLCloseWindow();

    fn PDLBlit(bitmap: *const u32);

    fn PDLGetKey(key: u8) -> u8;

    fn PDLDoWindowMessages() -> bool;
    fn PDLInit(
        title: *const u8,
        len: usize,
        x: u32,
        y: u32,
        width: u32,
        height: u32,
        scale: u32,
    ) -> bool;
}

#[repr(u8)]
pub enum Key {
    Left = 0x25,
    Right,
    Up,
    Down,

    Zero = 0x31,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,

    A = 0x41,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    Escape = 0x1B,
}

pub fn pdl_show_window() {
    unsafe { PDLShowWindow() }
}

pub fn pdl_hide_window() {
    unsafe { PDLHideWindow() }
}

pub fn pdl_resize_window(width: u32, height: u32) {
    unsafe { PDLResizeWindow(width, height) }
}

pub fn pdl_close_window() {
    unsafe { PDLCloseWindow() }
}

pub fn pdl_blit_bitmap(bitmap: &Box<[u32]>) {
    unsafe {
        PDLBlit(bitmap.as_ptr());
    }
}

pub fn pdl_get_key(key: u8) -> u8 {
    unsafe { PDLGetKey(key) }
}

pub fn pdl_do_window_messages() -> bool {
    unsafe { PDLDoWindowMessages() }
}

pub fn pdl_init(title: &str, x: u32, y: u32, width: u32, height: u32, scale: u32) -> bool {
    unsafe { PDLInit(title.as_ptr(), title.len(), x, y, width, height, scale) }
}
