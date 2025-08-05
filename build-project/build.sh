case "$(uname -s)" in
    Darwin*)
        OS="macos"
        LIB_EXT="dylib"
        WORKERS=$(sysctl -n hw.ncpu)
        ANTLR_SRC_LIB_PATH="antlr/build/runtime/libantlr4-runtime.4.13.2.$LIB_EXT"
        ;;
    Linux*)
        OS="linux"
        LIB_EXT="so"
        WORKERS=$(nproc)
        ANTLR_SRC_LIB_PATH="antlr/build/runtime/libantlr4-runtime.$LIB_EXT.4.13.2"
        ;;
    *)
        echo "Unsupported OS: $(uname -s)"
        exit 1;;
esac

case "$(uname -m)" in
    x86_64|amd64)
        ARCH="x86_64";;
    aarch64|arm64)
        ARCH="aarch64";;
    armv7l)
        ARCH="armv7";;
    i386|i686)
        ARCH="i386";;
    *)
        echo "Unsupported architecture: $(uname -m)"
        exit 1;;
esac

TEMP_DIR=tmp
if [ -d "$TEMP_DIR" ]; then
    rm -rf "$TEMP_DIR"
fi
mkdir $TEMP_DIR
cd $TEMP_DIR || exit 1

curl -L -o antlr.zip https://www.antlr.org/download/antlr4-cpp-runtime-4.13.2-source.zip
mkdir antlr
unzip antlr.zip -d antlr
cmake -S antlr -B antlr/build -DCMAKE_BUILD_TYPE=Release
cmake --build antlr/build -j"$WORKERS"

LOGOS_LIB_PATH="../../external/lib/$ARCH/$OS"
LIB_ANTLR_DEST="$LOGOS_LIB_PATH/libantlr4.$LIB_EXT"

cp $ANTLR_SRC_LIB_PATH $LIB_ANTLR_DEST
chmod +w $LIB_ANTLR_DEST
