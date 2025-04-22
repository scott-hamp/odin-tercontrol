#!/usr/bin/bash

build_linux () {

    gcc -fPIC -c tercontrol.c -o tercontrol.o
    gcc -shared -o libtercontrol.so tercontrol.o

    # To inspect the library: 
    # nm -D libtercontrol.so | grep tc_

}

build_windows () {

    gcc -c tercontrol.c -o tercontrol.o
    gcc -shared -o tercontrol.dll tercontrol.o -Wl,--out-implib,libtercontrol.a

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