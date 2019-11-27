mkdir target/macostest/

cargo build
rustc testapi.rs --extern pdl_sys=target/debug/libpdl_sys.rlib --out-dir target/macostest