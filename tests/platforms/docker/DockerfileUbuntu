FROM ubuntu:latest

RUN apt-get update &&  \
    DEBIAN_FRONTEND=noninteractive apt-get install -y  \
    cmake \
    clang-19 \
    llvm-19-dev \
    libclang-19-dev libclang-cpp19-dev \
    libantlr4-runtime-dev \
    curl libcurlpp-dev \
    zlib1g zlib1g-dev libzstd-dev \
    libedit-dev \
    uuid-dev \
    unzip

RUN update-alternatives --install /usr/bin/clang clang /usr/lib/llvm-19/bin/clang 100
RUN update-alternatives --install /usr/bin/clang++ clang++ /usr/lib/llvm-19/bin/clang++ 100

WORKDIR /app/

RUN make -B build

CMD ["/bin/bash"]
