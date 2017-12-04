set(net_SRCS
    ./Cfg.cpp
    ./ConfigScript.cpp
    ./GlobalObject.cpp
    ./Client.cpp
    ./Log.cpp
    ./dllmain.cpp

  )

add_library(rgc_client SHARED ${base_SRCS})
target_link_libraries(rgc_client rgc_base rgc_net)

install(TARGETS rgc_client DESTINATION lib)

file(GLOB HEADERS "*.h")

install(FILES ${HEADERS} DESTINATION include/Client)

