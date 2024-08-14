.SILENT: build buildAndRun run

build: grammar/parser.y grammar/lexer.l
	rm -rf gen
	mkdir gen
	bison -v -d -o gen/parser.c grammar/parser.y
	flex -o gen/lexer.c grammar/lexer.l
	gcc -o mylang include/cJSON.c gen/parser.c gen/lexer.c compiler/compiler.c ast/ast.c main.c

buildAndRun:
	rm -f mylang
	$(MAKE) build
	$(MAKE) run

run: mylang
	./mylang
