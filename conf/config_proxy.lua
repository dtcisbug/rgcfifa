cfg:setTcpPort(8102);
cfg:setServerType(5); -- Game - 0 | DB - 1 | Social - 2 | Login - 3 | Room - 4 | proxy - 5
cfg:setServerUID(1); 
-- para: type,uid,ip,port
cfg:addConnectList(0,1,"127.0.0.1",8100); --game
cfg:addConnectList(1,1,"127.0.0.1",8101); --db
--cfg:addConnectList(2,1,"127.0.0.1",1113);
--cfg:setTcpPort(1111);
--cfg:setTcpPort(1111);
