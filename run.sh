#!/bin/sh
#./build/debug/bin/rgc_server conf/config_game.lua game & 
#./build/debug/bin/rgc_server conf/config_db.lua db & 
#./build/debug/bin/rgc_server conf/config_proxy.lua proxy & 

PARA=$1
main()
{
    case $PARA in 
        game)
        LaunchPara1=conf/config_game.lua
        LaunchPara2=game
        ;;
        db)
        LaunchPara1=conf/config_db.lua
        LaunchPara2=db
        ;;
        proxy)
        LaunchPara1=conf/config_proxy.lua
        LaunchPara2=proxy
        ;;
        *)
            ./kill.sh && sleep 2
            ./build/debug/bin/rgc_server conf/config_game.lua game & 
            ./build/debug/bin/rgc_server conf/config_db.lua db & 
            ./build/debug/bin/rgc_server conf/config_proxy.lua proxy & 
        #echo "please enter para1 para2 !"
        exit
    esac
    ./build/debug/bin/rgc_server $LaunchPara1 $LaunchPara2 &
}
main


