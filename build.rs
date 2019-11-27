use std::env;
use std::process::Command;
#[cfg(target_os = "macos")]
fn run_platform_build() {
	if !Command::new("./macos_build.sh").status().expect("Failed to run macOS build").success() {
		panic!("Failed to build macos library!");
	}

	println!("cargo:rustc-link-lib=framework=Foundation");
	println!("cargo:rustc-link-lib=framework=Cocoa");
}

#[cfg(target_os = "windows")]
fn run_platform_build() {
	if !Command::new("win32_build.bat").status().expect("Failed to run win32 build").success() {
		panic!("Failed to build macos library!");
	}

	println!("cargo:rustc-link-lib=dylib=user32");
	println!("cargo:rustc-link-lib=dylib=gdi32");
}

fn main() {
	let out_dir = env::var("OUT_DIR").unwrap();

	run_platform_build();

	println!("cargo:rustc-link-search=native={}", out_dir);
	println!("cargo:rustc-link-lib=static=pdl");
}