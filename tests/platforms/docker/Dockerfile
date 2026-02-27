FROM ubuntu:latest

RUN apt-get update &&  \
    DEBIAN_FRONTEND=noninteractive apt-get install -y  \
    cmake \
    clang-21 \
    llvm-21-dev \
    libclang-21-dev libclang-cpp21-dev \
    curl libcurlpp-dev \
    zlib1g zlib1g-dev libzstd-dev \
    libedit-dev \
    uuid-dev \
    unzip

RUN update-alternatives --install /usr/bin/clang clang /usr/lib/llvm-21/bin/clang 100
RUN update-alternatives --install /usr/bin/clang++ clang++ /usr/lib/llvm-21/bin/clang++ 100

WORKDIR /app/

#RUN make -B build

CMD ["/bin/bash"]
