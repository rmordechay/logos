copy_libs:
	cmake --build cmake-build-debug --target lgslib -j 8
	cp cmake-build-debug/liblgslib.a /Users/r.mordechay/Desktop/Programming/logos/stdlib/lgslib.a

emit_llvm test.c:
	clang -S -emit-llvm test.c -o test.ll