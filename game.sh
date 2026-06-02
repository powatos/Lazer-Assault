#!/bin/bash

GAME_TARGET=LazerAssaultGame # replace with your target executable 

OBJDIR=build/
LOGFILE=logs/debug.log

SCRIPT=$(basename "$0")
CBTYPE=${2:-Debug}

case "$1" in
    "conf") # ./game conf Debug|Release, generate build files
        cmake -B $OBJDIR -DCMAKE_BUILD_TYPE=$CBTYPE
        echo "Rebuild complete"
        ;;
    "build"|"b") # ./game build|b, build project
        cmake --build $OBJDIR
        echo "Build complete"
        ;;
    "run"|"r") # ./game run|r, run game
        if  [[ -f $OBJDIR/$GAME_TARGET ]]; then
            ./$OBJDIR/$GAME_TARGET
        else
            echo "Invalid game target"
            exit 1
        fi
        ;;
    "clean"|"-c") # ./game clean|-c, reset build
        rm -rf $OBJDIR
        echo "Cleaned up binaries"
        ;;
    "flush"|"-f") # ./game flush|-f, flush log file
        > $LOGFILE
	    echo "Flushed $LOGFILE"
        ;;
    *)
        echo "Invalid argument"
        exit 1
        ;;

esac