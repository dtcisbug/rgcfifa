set(net_SRCS
    ./Cfg.cpp
    ./ConfigScript.cpp
    ./GlobalObject.cpp
    ./Main.cpp
    ./WorldServer.cpp
    ./Log.cpp
    ./Logic.cpp

    ../MsgHandler/MsgHandler.cpp
    ../MsgHandler/MsgPopHandler.cpp

  )

ADD_EXECUTABLE(rgc_server ${net_SRCS})
#target_link_libraries(rgc_server rgc_base rgc_net ${SCRIPT_LIB} dl mono-2.0 )
target_link_libraries(rgc_server rgc_base rgc_net ${SCRIPT_LIB} dl ${MONO_LIB} rt)

install(TARGETS rgc_server DESTINATION bin)

file(GLOB HEADERS "*.h")

install(FILES ${HEADERS} DESTINATION include/Server)

