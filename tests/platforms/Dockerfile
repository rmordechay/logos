FROM debian:latest
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y cmake build-essential lsb-release
RUN rm -rf /var/lib/apt/lists/*
#RUN #wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh 17 all && rm llvm.sh
#RUN #update-alternatives --install /usr/bin/cc cc /usr/bin/clang-17 100
#RUN #update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-17 100

WORKDIR app/

COPY src src/
COPY external external/
COPY include include/
COPY project project/
COPY stdlib stdlib/
COPY CMakeLists.txt CMakeLists.txt
COPY main.cpp main.cpp

WORKDIR build/
RUN cmake ..
RUN make -j 4

CMD ["/bin/bash"]