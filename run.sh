#!/bin/sh
./build/debug/bin/rgc_server conf/config_game.lua game & 
./build/debug/bin/rgc_server conf/config_db.lua db & 
./build/debug/bin/rgc_server conf/config_proxy.lua proxy & 

