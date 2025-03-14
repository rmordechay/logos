generate_grammar:
	rm -rf src/parser
	java -jar external/bin/antlr.jar -no-listener -Dlanguage=Cpp -o src/parser Logos.g4
	mv src/parser/*.h include/parser/

run_llvm:
	cd project/build && clang MyObject.ll Main.ll ../../stdlib/lgslib.ll -o output
	cd project/build && ./output