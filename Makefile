.PHONY: all configure build clean run
all: configure build
build_and_run: configure build run

configure:
	@mkdir -p build
	@cd build && cmake ..

build:
	@cd build && make -j16

clean:
	rm -rf build

run:
	@cd project && ../build/lgs run .

generate_grammar:
	rm -rf src/parser
	java -jar external/bin/antlr.jar -no-listener -Dlanguage=Cpp -o src/parser Logos.g4
	mv src/parser/*.h include/parser/

run_llvm:
	cd project/build && clang Main.ll ../../stdlib/lgslib.a -o output
	cd project/build && ./output

run_linux_docker tests/platforms/Dockerfile:
	docker build -f tests/platforms/Dockerfile -t linux . && docker run -it -v $(pwd):/app linux /bin/bash && cmake .. && make -j 5