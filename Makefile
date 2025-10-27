build:
	cmake -S . -B build
	cmake --build build -j5

run: build
	cd build && ./lgs run ../project

run_linux_docker tests/platforms/DockerfileUbuntu:
	docker build -f tests/platforms/ubuntu/Dockerfile -v $(pwd):/app -t linux . && docker run -it -v $(pwd):/app linux

install_alpine:
	qemu-img create -f qcow2 linux-x86.qcow2 10G
	qemu-system-x86_64 \
	  -machine accel=kvm \
	  -cpu host \
	  -m 6G \
	  -smp 4 \
	  -drive file=linux-x86.qcow2,format=qcow2 \
	  -cdrom alpine-x86_64.iso \
	  -boot d \
	  -net nic -net user \
	  -nographic
	setup-alpine -q
	apk add git cmake
	apk add clang19 llvm19-dev curl curl-dev libxml2-dev
	ln -sf /usr/bin/clang-19 /usr/bin/clang
	ln -sf /usr/bin/clang++-19 /usr/bin/clang++
	ln -sf /usr/bin/clang-19 /usr/bin/cc
	ln -sf /usr/bin/clang++-19 /usr/bin/c++
	git clone -b dev https://github.com/rmordechay/logos
	update-alternatives --install /usr/bin/cc cc /usr/lib/llvm19/bin/clang 100
	update-alternatives --install /usr/bin/c++ c++ /usr/lib/llvm19/bin/clang++ 100
