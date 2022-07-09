#!/bin/bash

until /root/pigeon-war/build/src/lobby/lobby -g /root/pigeon-war/build/pigeon_war; do
    "restarting server" >&2
    sleep 1
done

