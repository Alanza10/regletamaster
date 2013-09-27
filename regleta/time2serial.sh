#!/bin/sh
TZ_adjust=+2;  echo T$(($(date +%s)+60*60*$TZ_adjust)) > /dev/ttyUSB0
