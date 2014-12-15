TARGET = experiment_1_4_kthrd.ko
MDIR = arch/arm/experiment_1_4_kthrd
DRIVER_OBJS =   aprof.o
CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
DEST = /lib/modules/$(CURRENT)/kernel/$(MDIR)
obj-m := experiment_1_4_kthrd.o
experiment_1_4_kthrd-objs := $(DRIVER_OBJS)
default:
	$(MAKE) -C $(KDIR) M=$$PWD
install:
	@if test -f $(DEST)/$(TARGET).orig; then\
		echo  "Backup of experiment_1_4_kthrd.ko already exists."; \
	else \
		echo  "Creating a backup of experiment_1_4_kthrd.ko."; \
		mv -v $(DEST)/$(TARGET) $(DEST)/$(TARGET).orig; \
	fi
	su -c "cp $(TARGET) $(DEST) &#038;&#038; /sbin/depmod -a"
revert:
	@echo  "Reverting to the original experiment_1_4_kthrd.ko."
	@mv -v $(DEST)/$(TARGET).orig $(DEST)/$(TARGET) 
clean:
	rm -f *.o experiment_1_4_kthrd.ko .*.cmd .*.flags *.mod.c
-include $(KDIR)/Rules.make
