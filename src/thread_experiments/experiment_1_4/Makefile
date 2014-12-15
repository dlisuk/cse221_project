TARGET = e14.ko
MDIR = arch/arm/e14
DRIVER_OBJS =   exp14.o
CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
DEST = /lib/modules/$(CURRENT)/kernel/$(MDIR)
obj-m := e14.o
e14-objs := $(DRIVER_OBJS)
default:
	$(MAKE) -C $(KDIR) M=$$PWD
install:
	@if test -f $(DEST)/$(TARGET).orig; then\
		echo  "Backup of e14.ko already exists."; \
	else \
		echo  "Creating a backup of e14.ko."; \
		mv -v $(DEST)/$(TARGET) $(DEST)/$(TARGET).orig; \
	fi
	su -c "cp $(TARGET) $(DEST) &#038;&#038; /sbin/depmod -a"
revert:
	@echo  "Reverting to the original e14.ko."
	@mv -v $(DEST)/$(TARGET).orig $(DEST)/$(TARGET) 
clean:
	rm -f *.o e14.ko .*.cmd .*.flags *.mod.c
-include $(KDIR)/Rules.make
