generate_grammar:
	rm -rf src/parser
	java -jar external/bin/antlr.jar -no-listener -Dlanguage=Cpp -o src/parser Logos.g4
	mv src/parser/*.h include/parser/

run_llvm:
	cd project/build && clang Obj1.ll Obj2.ll Main.ll ../../stdlib/array.ll ../../stdlib/lgslib.ll -o output
	cd project/build && ./output

run_linux_docker tests/platforms/Dockerfile:
	docker build -f tests/platforms/Dockerfile -t linux . && docker run -it -v $(pwd):/app linux /bin/bash && cmake .. && make -j 5