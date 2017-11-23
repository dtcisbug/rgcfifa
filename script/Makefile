OS := $(shell uname)

SRCS := lua_tinker.cpp Script.cpp

OBJS_ := $(SRCS:.cpp=.o)
OBJS := $(OBJS_:.c=.o)

LIBNAME = libscript
ifeq ($(LUAJIT), true)
	INCLS := -Iluajit/src
	LUA_O := .libluajit/*.o
ifeq ($(TARGETSO), true)
	TARGETS = $(LIBNAME).jit.so
else
	TARGETS = $(LIBNAME).jit.a
endif
else
	INCLS := -Ilua
	LUA_O := lua/*.o
ifeq ($(TARGETSO), true)
	TARGETS = $(LIBNAME).so
else
	TARGETS = $(LIBNAME).a
endif
endif

INCLS += -I..
LIBS := $(LIBS)

.PHONY: all install clean distclean luajit lua

all: $(TARGETS)

install: $(TARGETS) $(OBJS)

clean: 
	$(AT)$(RM) -f *.o *.a $(OBJS) $(TARGETS)
ifeq ($(LUAJIT), true)
	$(AT)$(MAKE) clean -C luajit
else
	$(AT)$(MAKE) clean -C lua
endif

$(LIBNAME).so: _lua $(OBJS)
	$(GCC) --dynmaic $@ $(OBJS) $(LUA_O)

$(LIBNAME).a: _lua $(OBJS)
	$(AR) ur $@ $(OBJS) $(LUA_O)

$(LIBNAME).jit.so: _luajit $(OBJS)
	$(GCC) --dynmaic $@ $(OBJS) $(LUA_O)
	$(AT) cp $@ $(LIBNAME).so

$(LIBNAME).jit.a: _luajit $(OBJS)
	$(AR) ur $@ $(OBJS) $(LUA_O)
	$(AT) cp $@ $(LIBNAME).a

_lua:
	$(AT)$(MAKE) linux -C lua

_luajit:
	$(AT)$(MAKE) -C luajit
	$(AT)if [ -f luajit/src/libluajit.a ]; then\
			mkdir .libluajit;\
			cd .libluajit && ar x ../luajit/src/libluajit.a; \
		fi

lua:
	$(AT)$(MAKE)

luajit:
	$(AT)$(MAKE) LUAJIT=true

luajitclean:
	$(AT)$(MAKE) clean LUAJIT=true

release: $(OBJS)
	$(OBJCOPY) --only-keep-debug $@ $@.symbol

%.o: %.c
	$(AT)$(GCC) $(CFLAGS) $(INCLS) -o $@ -c $<

%.o: %.cpp
	$(AT)$(CXX) $(CPPFLAGS) $(INCLS) -o $@ -c $<

