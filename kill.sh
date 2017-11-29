#!/bin/sh
ps -ef |grep rgc_server |grep game | awk  '{print $2}' |xargs kill >/dev/null 2>&1
ps -ef |grep rgc_server |grep db | awk  '{print $2}' |xargs kill >/dev/null 2>&1
ps -ef |grep rgc_server |grep proxy | awk  '{print $2}' |xargs kill >/dev/null 2>&1

