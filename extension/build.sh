#!/bin/bash

gcc -fPIC -shared -pthread -m32 -o janus.so janus.c
