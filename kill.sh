#!/bin/sh

PARA=$1
main()
{
    case $PARA in 
        game)
            ps -ef |grep rgc_server |grep game | awk  '{print $2}' |xargs kill >/dev/null 2>&1
        ;;
        db)
            ps -ef |grep rgc_server |grep db | awk  '{print $2}' |xargs kill >/dev/null 2>&1
        ;;
        proxy)
            ps -ef |grep rgc_server |grep proxy | awk  '{print $2}' |xargs kill >/dev/null 2>&1
        ;;
        login)
            ps -ef |grep rgc_server |grep login | awk  '{print $2}' |xargs kill >/dev/null 2>&1
        ;;
        *)
            ps -ef |grep rgc_server |grep game | awk  '{print $2}' |xargs kill >/dev/null 2>&1
            ps -ef |grep rgc_server |grep db | awk  '{print $2}' |xargs kill >/dev/null 2>&1
            ps -ef |grep rgc_server |grep proxy | awk  '{print $2}' |xargs kill >/dev/null 2>&1
            ps -ef |grep rgc_server |grep login | awk  '{print $2}' |xargs kill >/dev/null 2>&1
        #echo "please enter para1 para2 !"
        exit
    esac
}
main






