FROM ubuntu:latest

RUN apt-get update && apt-get install -y cmake build-essential lsb-release wget software-properties-common gnupg file libedit-dev zlib1g-dev libzstd-dev libcurl4-openssl-dev git
RUN rm -rf /var/lib/apt/lists/*
RUN wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh 20 all && rm llvm.sh
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang-19 100
RUN update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-19 100
ENV PATH="/lib/llvm-19/bin:${PATH}"

WORKDIR /app/

CMD ["/bin/bash"]
