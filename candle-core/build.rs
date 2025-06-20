fn main() {
    // Compile the C++ wrapper
    cc::Build::new()
        .cpp(true)
        .file("src/eigen_wrapper.cpp")
        .include("../third_party/eigen")
        .compile("libeigen_wrapper.a");

    // Link the compiled C++ library
    println!("cargo:rustc-link-lib=static=eigen_wrapper");
    println!("cargo:rerun-if-changed=src/eigen_wrapper.cpp");
}