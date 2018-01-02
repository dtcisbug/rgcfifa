cfg:setTcpPort(8101);
cfg:setServerType(1); -- Game - 0 | DB - 1 | Social - 2 | Login - 3 | Room - 4 | proxy - 5
cfg:setServerUID(1); 
cfg:setServerLogName("DB1"); 
cfg:setServerDllName("DB.dll"); 
-- para: type,uid,ip,port
cfg:addConnectList(5,1,"127.0.0.1",8102); -- proxy 
--cfg:addConnectList(1,1,"127.0.0.1",1112);
--cfg:addConnectList(2,1,"127.0.0.1",1113);
cfg:setDatabase("127.0.0.1",3306,"root","123456","TropicalStorm");
