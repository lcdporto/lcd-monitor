#!/bin/bash
MAINFILE="code.ino"
BOARD="arduino:avr:nano:cpu=atmega168"
OPERATION="--verify"


SKETCHBOOK_PATH="/home/jfig/snap/arduino-mhall119/current/Arduino"
CMD="/snap/arduino-mhall119/current/arduino"
BUILD_PATH="/home/jfig/tmp/arduino_build"
# --------------------------------------------------------------------

[[ "$BOARD" != "" ]] && BOARD="--board $BOARD"

[[ "$SKETCHBOOK_PATH" != "" ]] && {
  prefs="$prefs --pref sketchbook.path=$SKETCHBOOK_PATH "
}

[[ "$BUILD_PATH" != "" ]] && {
  mkdir -p "$BUILD_PATH"
  prefs="$prefs --pref build.path=$BUILD_PATH "
}


CMD="$CMD $OPERATION $BOARD $prefs $MAINFILE"
echo executing: \""$CMD"\"
$CMD
