set(net_SRCS
    ./Cfg.cpp
    ./GlobalObject.cpp
    ./Main.cpp
    ./WorldServer.cpp
    ./Log.cpp

  )

ADD_EXECUTABLE(rgc_server ${net_SRCS})
target_link_libraries(rgc_server rgc_base rgc_net)

install(TARGETS rgc_server DESTINATION bin)

file(GLOB HEADERS "*.h")

install(FILES ${HEADERS} DESTINATION include/Server)

