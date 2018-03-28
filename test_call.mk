SRC_DIR = .

FINAL_TARGET = $(OUT_DIR)/test_call

ifndef PRJROOT

COMPILE = arm-none-linux-gnueabi-g++
LINK = arm-none-linux-gnueabi-g++
LDFLAGS = -L /home/yang/Documents/sipApp_tkj/bin \
-L /home/rootfs/vt/fs_k2268s/mnt/user_rootfs/usr/lib \
-leXosip2 -losip2 -losipparser2 -lpthread -lUserAgent \
/home/yang/Downloads/googlemock/make/gmock_main.a
INCLUDE_FLAGS = -I/usr/local/CrossCompile/include -I/work/Software/Application/viewtalk/coreapi -I/home/rootfs/vt/k2268s/share/sipApp_tkj -I/home/rootfs/vt/k2268s/share/sipApp_tkj/include -I/home/yang/Downloads/googletest/include -I/home/yang/Downloads/googlemock/include
OBJS_DIR = ./objs/mips
OUT_DIR = ./bin/mips

else

COMPILE = g++
LINK = g++
LDFLAGS = ./bin/i386/UserAgent.i386.a /usr/local/lib/libeXosip2.a /usr/local/lib/libosip2.a /usr/local/lib/libosipparser2.a -lpthread
INCLUDE_FLAGS = -I/work/Software/Application/viewtalk/coreapi -I/home/yang/Documents/sipApp_tkj -I/home/yang/Documents/sipApp_tkj/include
OBJS_DIR = ./objs/i386
OUT_DIR = ./bin/i386

endif

CFLAGS = -Wall -ggdb -O2 

OBJS = $(OBJS_DIR)/TestForUA.o \
$(OBJS_DIR)/test_call.o

.PHONY : all
all : $(FINAL_TARGET)

$(FINAL_TARGET) : $(OBJS)
	$(LINK) -o $(FINAL_TARGET) $(OBJS) $(LDFLAGS)

$(OBJS_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(COMPILE) -c $(CFLAGS) $< -o $@ $(INCLUDE_FLAGS)

.PHONY : clean
clean :
	rm -rf $(OBJS) $(FINAL_TARGET)

.PHONY : clean_bin
clean_bin :
	rm -rf $(FINAL_TARGET)
