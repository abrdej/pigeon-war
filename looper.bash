#!/bin/bash

until /root/pigeon-war/build/pigeonwar_server; do
    "restarting servers" >&2
    sleep 1
done

