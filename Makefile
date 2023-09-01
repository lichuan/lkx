CC = gcc
CFLAGS = -O2
CPPFLAGS =
LDFLAGS =
LKX_C_INC = cimpl
INC = -I$(LKX_C_INC)
OBJOUT = objfiles
VPATH = $(LKX_C_INC)
LKX_OBJS = lkx/array.o lkx/istruct.o lkx/ostruct.o lkx/vm.o
SAMPLE_OBJ := lkxsample.o
DEPFILE = $(OBJOUT)/depfile

.PHONY: all clean dep
all: lkxsample

OBJS := $(addprefix $(OBJOUT)/, $(LKX_OBJS) $(SAMPLE_OBJ))
CFILES = $(SAMPLE_OBJ:.o=.c) $(addprefix $(LKX_C_INC)/, $(LKX_OBJS:.o=.c))

lkxsample: $(OBJS)
	$(CC) -o $@ $^

dep:
	$(foreach objpath, $(OBJS), $(shell mkdir -p $(dir $(objpath))))
	$(shell rm -f $(DEPFILE))
	$(foreach cf, $(CFILES), $(shell $(CC) $(INC) $(cf) -MM -MT $(addprefix $(OBJOUT)/, $(subst $(LKX_C_INC)/,,$(cf:.c=.o))) >> $(DEPFILE)))

$(OBJS): $(OBJOUT)/%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

-include $(DEPFILE)

clean:
	find $(OBJOUT) -name *.o | xargs rm -f
	rm -f $(DEPFILE)
	rm -f lkxsample
