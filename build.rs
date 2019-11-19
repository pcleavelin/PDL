use std::env;
use std::process::Command;
use std::path::Path;

fn main() {
	let out_dir = env::var("OUT_DIR").unwrap();

	Command::new("win32_build.bat").status().unwrap();

	println!("cargo:rustc-link-search=native={}", out_dir);
	println!("cargo:rustc-link-lib=static=pdl");
}