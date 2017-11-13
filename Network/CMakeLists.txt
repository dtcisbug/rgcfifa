set(net_SRCS
    ./ClientConn.h
    ./Network.cpp
    ./TcpServerWrapper.h
    ./TcpServer.cpp
    ./TcpServer.h
    ./TcpConduit.h
    ./GameClient.h
    ./TcpConduit.cpp
    ./Network.h
    ./GameClient.cpp
    ./ClientConn.cpp
    
  )

add_library(rgc_net ${net_SRCS})
target_link_libraries(rgc_net rgc_base)

install(TARGETS rgc_net DESTINATION lib)

file(GLOB HEADERS "*.h")

install(FILES ${HEADERS} DESTINATION include/Network)

