#!/bin/sh

gdb -q -nx -ex 'target remote :1235'
