FROM ubuntu:latest

RUN apt-get update && apt-get install -y cmake build-essential lsb-release wget software-properties-common gnupg file libedit-dev zlib1g-dev libzstd-dev libcurl4-openssl-dev git
RUN rm -rf /var/lib/apt/lists/*
RUN wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh 19 all && rm llvm.sh
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang-19 100
RUN update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-19 100
RUN wget https://github.com/llvm/llvm-project/releases/download/llvmorg-19.1.0/llvm-project-19.1.0.src.tar.xz
RUN tar -xf llvm-project-19.1.0.src.tar.xz
RUN rm llvm-project-19.1.0.src.tar.xz

RUN mkdir /app
WORKDIR /app/build
