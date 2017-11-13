set(base_SRCS
    ./ErrorHandler.cpp
    ./Debugger.cpp
    ./RandomStream.cpp
    ./RefCountedObject.cpp
    ./SHA1Engine.cpp
    ./Environment.cpp
    ./Thread.cpp
    ./Timestamp.cpp
    ./SignalHandler.cpp
    ./Bugcheck.cpp
    ./Zip.cpp
    ./File.cpp
    ./Exception.cpp
    ./TimeUtil.cpp
    ./URandom.cpp
    ./NumberFormatter.cpp
    ./Path.cpp
    ./DirectoryIterator.cpp
    ./Timespan.cpp
    ./DigestEngine.cpp
    ./ThreadLocal.cpp
    ./Mutex.cpp
    ./PseudoRandom.cpp
    ./Random.cpp
    ./Runnable.cpp
    ./AtomicCounter.cpp
    ./Event.cpp
    ./Ascii.cpp
    ./TInf.cpp
    ./StringTokenizer.cpp
    ./MemBlockPool.cpp
    ./LoadingCounter.cpp
    ./Config.cpp
  )

add_library(rgc_base ${base_SRCS})
target_link_libraries(rgc_base pthread z m)

install(TARGETS rgc_base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/Common)
