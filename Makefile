build:
	cmake -S . -B build
	cmake --build build -j5

run: build
	cd build && ./lgs run ../project

run_linux_docker tests/platforms/DockerfileUbuntu:
	docker build -f tests/platforms/ubuntu/Dockerfile -v $(pwd):/app -t linux . && docker run -it -v $(pwd):/app linux


