#!/bin/sh

if [ "$SCRIPT" = "code" ]; then
    ./app
elif [ "$SCRIPT" = "simple_code" ]; then
    ./simple_app
else
    echo "No valid script specified."
fi
