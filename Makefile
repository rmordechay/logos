build:
	cmake -S . -B build
	cmake --build build -j5

build_debug:
	cmake -S . -B build
	cmake --build build -j5

run: build
	cd build && ./lgs run ../project

generate_grammar:
	rm -rf src/parser
	java -jar bin/antlr.jar -no-listener -Dlanguage=Cpp -o src/parser Logos.g4
	mv src/parser/*.h include/parser/

run_linux_docker tests/platforms/DockerfileUbuntu:
	docker build -f tests/platforms/DockerfileUbuntu -v $(pwd):/app -t linux . && docker run -it -v $(pwd):/app linux

install_alpine:
	setup-alpine -q
	apk add git make cmake curl clang19 llvm19-dev curl-dev libxml2-dev dpkg
	update-alternatives --install /usr/bin/cc cc /usr/lib/llvm19/bin/clang 100
	update-alternatives --install /usr/bin/c++ c++ /usr/lib/llvm19/bin/clang++ 100

run_qemu:
	qemu-img create -f qcow2 linux-x86.qcow2 30G
	qemu-system-x86_64 \
	  -machine accel=tcg \
	  -cpu max \
	  -m 6G \
	  -drive file=linux-x86.qcow2,format=qcow2 \
	  -cdrom alpine-x86_64.iso \
	  -boot d \
	  -net nic -net user \
	  -nographic
