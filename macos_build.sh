gcc -c src/macOS/macOS_pdl.m -o $OUT_DIR/macOS_pdl.obj
gcc -c src/macOS/Delegates.m -o $OUT_DIR/macOS_delegates.obj
ar rcs $OUT_DIR/libpdl.a $OUT_DIR/macOS_delegates.obj $OUT_DIR/macOS_pdl.obj