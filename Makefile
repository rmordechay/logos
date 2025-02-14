generate_grammar:
	rm -rf src/parser
	java -jar external/bin/antlr.jar -no-listener -Dlanguage=Cpp -o src/parser Logos.g4

generate_code:
	cd codegen && clang -o output output.ll

emit_llvm:
	cd codegen && clang -c output.ll -o output.o
	cd codegen && clang output.o -o output
	codegen/output
	#rm codegen/output codegen/output.o
