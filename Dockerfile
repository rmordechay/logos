FROM debian:latest

RUN apt-get update
RUN apt-get install -y build-essential lsb-release wget software-properties-common gnupg cmake file vim libantlr4-runtime-dev
RUN wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh 17 all && rm llvm.sh
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang-17 100
RUN update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-17 100
RUN apt-get clean
RUN rm -rf /var/lib/apt/lists/*

WORKDIR app/

COPY external/ external/
COPY src/ src/
COPY include/ include/
COPY project/ project/
COPY stdlib/ stdlib/
COPY CMakeLists.txt CMakeLists.txt
COPY main.cpp main.cpp

WORKDIR build/
RUN cmake ..
RUN make -j 4

CMD ["/bin/bash"]