LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

BASE_SOURCES := \
	./Common/ErrorHandler.cpp \
    ./Common/Debugger.cpp \
    ./Common/RandomStream.cpp \
    ./Common/RefCountedObject.cpp \
    ./Common/SHA1Engine.cpp \
    ./Common/Environment.cpp \
    ./Common/Thread.cpp \
    ./Common/Timestamp.cpp \
    ./Common/SignalHandler.cpp \
    ./Common/Bugcheck.cpp \
    ./Common/Zip.cpp \
    ./Common/File.cpp \
    ./Common/Exception.cpp \
    ./Common/TimeUtil.cpp \
    ./Common/URandom.cpp \
    ./Common/NumberFormatter.cpp \
    ./Common/Path.cpp \
    ./Common/DirectoryIterator.cpp \
    ./Common/Timespan.cpp \
    ./Common/DigestEngine.cpp \
    ./Common/ThreadLocal.cpp \
    ./Common/Mutex.cpp \
    ./Common/PseudoRandom.cpp \
    ./Common/Random.cpp \
    ./Common/Runnable.cpp \
    ./Common/AtomicCounter.cpp \
    ./Common/Event.cpp \
    ./Common/Ascii.cpp \
    ./Common/TInf.cpp \
    ./Common/StringTokenizer.cpp \
    ./Common/MemBlockPool.cpp \
    ./Common/LoadingCounter.cpp \
	./Common/Config.cpp 	
NETWORK_SOURCES := \
	./Network/Network.cpp \
    ./Network/TcpServer.cpp \
    ./Network/TcpConduit.cpp \
    ./Network/GameClient.cpp \
    ./Network/ClientConn.cpp 
CLIENT_SOURCES := \
	./Client/GlobalObject.cpp \
	./Client/Client.cpp \
	./Client/Log.cpp \
	./Client/dllmain.cpp
LIBEVENT_SOURCES := \
	./libevent/event.c 		 	./libevent/evmap.c 			./libevent/evthread.c 	 		./libevent/evutil.c 		./libevent/log.c 			./libevent/select.c 		./libevent/signal.c 		./libevent/strlcpy.c ./libevent/evutil_time.c ./libevent/epoll.c ./libevent/poll.c ./libevent/buffer.c ./libevent/bufferevent.c ./libevent/bufferevent_filter.c ./libevent/bufferevent_pair.c ./libevent/bufferevent_ratelim.c ./libevent/bufferevent_sock.c 

LIBEVENT_SOURCES1 := \
	./libevent/event.c 		 	./libevent/evmap.c 			./libevent/evthread.c 	 		./libevent/evutil.c 		./libevent/log.c 			./libevent/select.c 		./libevent/signal.c 		./libevent/strlcpy.c ./libevent/evutil_time.c ./libevent/epoll.c ./libevent/poll.c ./libevent/evutil_rand.c ./libevent/arc4random.c 

LOCAL_MODULE := rgc_client 
LOCAL_SRC_FILES := $(LIBEVENT_SOURCES) $(BASE_SOURCES) $(NETWORK_SOURCES) $(CLIENT_SOURCES)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/Network $(LOCAL_PATH)/Common $(LOCAL_PATH)/Client $(LOCAL_PATH)/libevent/include $(LOCAL_PATH)/libevent/include/event2 $(LOCAL_PATH)/libevent/include/sys 
LOCAL_LDLIBS += -lz -lm 
LOCAL_CPP_FEATURES := exceptions rtti 

include $(BUILD_SHARED_LIBRARY)


