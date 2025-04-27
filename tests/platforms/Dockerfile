FROM ubuntu:latest

RUN apt-get update && apt-get install -y cmake build-essential lsb-release wget software-properties-common gnupg
RUN rm -rf /var/lib/apt/lists/*
RUN wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh 19 all && rm llvm.sh
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang-19 100
RUN update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-19 100

RUN mkdir /app
WORKDIR /app/build
