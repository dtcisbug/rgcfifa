set(client_SRCS
    ./Cfg.cpp
    ./ConfigScript.cpp
    
    ./GlobalObject.cpp
    ./Client.cpp
    ./Log.cpp
    ./dllmain.cpp

  )

set(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")

add_library(rgc_client SHARED ${client_SRCS})
#target_link_libraries(rgc_client rgc_net rgc_base)
target_link_libraries(rgc_client)

install(TARGETS rgc_client DESTINATION lib)

file(GLOB HEADERS "*.h")

install(FILES ${HEADERS} DESTINATION include/Client)

