
generate_grammar:
	rm -rf logos/parser
	java -jar external/bin/antlr.jar -no-listener -Dlanguage=Cpp -o logos/parser Logos.g4

generate_code:
	cd codegen && \
	/opt/homebrew/opt/llvm/bin/llc output.ll -o output.o && \
	clang output.o -o output