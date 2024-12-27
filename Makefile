
generate_grammar:
	rm -rf logos/parser
	java -jar grammar/antlr.jar -no-listener -Dlanguage=Cpp -o logos/parser Logos.g4

generate_code:
	cd codegen && \
	rm output.ll && \
	../cmake-build-debug/logos && \
	/opt/homebrew/opt/llvm/bin/llc -filetype=obj output.ll -o output.o && \
	clang output.o -o output