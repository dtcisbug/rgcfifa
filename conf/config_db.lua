cfg:setTcpPort(8101);
cfg:setServerType(1); -- Game - 0 | DB - 1 | Social - 2 | Login - 3 | Room - 4 | proxy - 5
cfg:setServerUID(1); 
cfg:setServerLogName("DB1"); 
-- para: type,uid,ip,port
cfg:addConnectList(5,1,"127.0.0.1",8102); -- proxy 
--cfg:addConnectList(1,1,"127.0.0.1",1112);
--cfg:addConnectList(2,1,"127.0.0.1",1113);
--cfg:setTcpPort(1111);
--cfg:setTcpPort(1111);
