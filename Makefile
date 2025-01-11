
generate_grammar:
	rm -rf logos/parser
	java -jar external/bin/antlr.jar -no-listener -Dlanguage=Cpp -o logos/parser Logos.g4

generate_code:
	cd codegen && clang -o output output.ll

emit_llvm:
	clang -S -emit-llvm test.cpp