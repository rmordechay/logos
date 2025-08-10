build:
	cmake -S . -B build
	cmake --build build -j5

run: build
	cd build && ./lgs run ../project

generate_grammar:
	rm -rf src/parser
	java -jar bin/antlr.jar -no-listener -Dlanguage=Cpp -o src/parser Logos.g4
	mv src/parser/*.h include/parser/

run_llvm:
	cd project/build && clang IR/Main.ll ../../cmake-build-debug/stdlib/liblgslib.a -o output
	cd project/build && ./output

run_linux_docker tests/platforms/Dockerfile:
	docker build -f tests/platforms/Dockerfile -v $(pwd):/app -t linux . && docker run -it -v $(pwd):/app linux

run_qemu:
	qemu-img create -f qcow2 linux-x86.qcow2 5G
	qemu-system-x86_64 \
      -machine accel=tcg \
      -cpu max \
      -m 2G \
      -drive file=linux-x86.qcow2,format=qcow2 \
      -net nic -net user \
      -nographic
