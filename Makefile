build: grammar/parser.y grammar/lexer.l
	rm -rf gen
	mkdir gen
	bison -d -o gen/parser.c grammar/parser.y
	flex -o gen/lexer.c grammar/lexer.l
	gcc -o MyLang gen/parser.c gen/lexer.c ast/ast.c main.c

buildAndRun:
	rm -f Mylang
	@$(MAKE) build
	./Mylang

