set(net_SRCS
    ./Script.cpp
    ./lua_tinker.cpp
  )

add_library(script ${net_SRCS})
target_link_libraries(script rgc_base luajit)

install(TARGETS script DESTINATION bin)

file(GLOB HEADERS "*.h")

install(FILES ${HEADERS} DESTINATION include/script)

