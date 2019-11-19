mkdir target\win32test\

rustc testapi.rs --extern pdl_sys=target/debug/libpdl_sys.rlib -luser32 -lgdi32 --out-dir target/win32test