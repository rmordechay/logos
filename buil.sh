mkdir antlr
cd antlr || exit 1
curl -L -o antlr.zip https://www.antlr.org/download/antlr4-cpp-runtime-4.13.2-source.zip
unzip antlr.zip
#cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
#cmake --build build -j5