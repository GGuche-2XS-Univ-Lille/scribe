#!/bin/sh

usage() {
    exe_name=$(basename "$0")
    printf "\
Usage: %s <MANDATORY ARGUMENT>

  MANDATORY ARGUMENT:

    --board=<name> Specify the name of the board to build scribe for. Supported
                   boards can be found in the \"boards\" directory.
" "$exe_name"
    return 0
}

main() {
    base=$(dirname "$0")
    if [ "$#" -lt 1 ];
    then
        usage
        exit 1
    fi
    board=${1%=*}
    if ! [ "$board" = '--board' ];
    then
        usage
        exit 1
    fi
    name=${1#*=}
    printf 'BOARD = %s\n' "$name" > "$base"/toolchain.mk
    exit 0
}

main "$@"
