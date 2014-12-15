TARGET = e15_ver1.ko
MDIR = arch/arm/e15
DRIVER_OBJS =   exp15.o
CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
DEST = /lib/modules/$(CURRENT)/kernel/$(MDIR)
obj-m := e15_ver1.o
e15_ver1-objs := $(DRIVER_OBJS)
default:
	$(MAKE) -C $(KDIR) M=$$PWD
install:
	@if test -f $(DEST)/$(TARGET).orig; then\
		echo  "Backup of e15.ko already exists."; \
	else \
		echo  "Creating a backup of e15.ko."; \
		mv -v $(DEST)/$(TARGET) $(DEST)/$(TARGET).orig; \
	fi
	su -c "cp $(TARGET) $(DEST) &#038;&#038; /sbin/depmod -a"
revert:
	@echo  "Reverting to the original e15.ko."
	@mv -v $(DEST)/$(TARGET).orig $(DEST)/$(TARGET) 
clean:
	rm -f *.o e15.ko .*.cmd .*.flags *.mod.c
-include $(KDIR)/Rules.make
