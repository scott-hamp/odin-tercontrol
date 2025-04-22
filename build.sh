#!/usr/bin/bash

build_linux () {

    cd src/tercontrol
    ./build-lib.sh

    if [ -f "libtercontrol.so" ]; then

        cd ../..

        odin build src -out:app -extra-linker-flags:"-L./src/tercontrol -ltercontrol"

        if [ -f "app" ]; then

            mkdir -p output
            cp app output
            rm app

            cp src/tercontrol/libtercontrol.so output

        fi
    
    fi

}

build_windows () {

    cd src/tercontrol
    ./build-lib.sh

    if [ -f "libtercontrol.a" ]; then

        cd ../..

        odin build src -out:app.exe -extra-linker-flags:"-L.\\src\\tercontrol -ltercontrol"

        if [ -f "app.exe" ]; then

            mkdir -p output
            cp app.exe output
            rm app.exe

            cp src/tercontrol/tercontrol.dll output
            
        fi

    fi

}

os_name=$(uname -s)

case "$os_name" in
  Linux*)
    build_linux
    ;;
  Darwin*)
    echo "Mac is not supported."
    ;;
  CYGWIN* | MINGW*)
    build_windows
    ;;
  *)
    echo "Unknown or unsupported operating system: '$os_name'."
    ;;
esac