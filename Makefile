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
all: $(DEPFILE) lkxsample

OBJS := $(addprefix $(OBJOUT)/, $(LKX_OBJS) $(SAMPLE_OBJ))
CFILES = $(SAMPLE_OBJ:.o=.c) $(addprefix $(LKX_C_INC)/, $(LKX_OBJS:.o=.c))
DEP_COUNT = $(shell grep -s depfile $(DEPFILE) | wc -l)

lkxsample: $(OBJS)
	$(CC) -o $@ $^

dep:
	@echo "depfile obj count: $(DEP_COUNT), makefile obj count: $(words $(OBJS))"
	$(shell rm -f $(DEPFILE))
	$(foreach cf, $(CFILES), $(shell $(CC) $(INC) -MM $(cf) -MG -MP -MT $(addprefix $(DEPFILE)\ $(OBJOUT)/, $(subst $(LKX_C_INC)/,,$(cf:.c=.o))) >> $(DEPFILE)))

$(DEPFILE):
	$(foreach objpath, $(OBJS), $(shell mkdir -p $(dir $(objpath))))
	$(shell rm -f $@)
	$(foreach cf, $(CFILES), $(shell $(CC) $(INC) -MM $(cf) -MG -MP -MT $(addprefix $@\ $(OBJOUT)/, $(subst $(LKX_C_INC)/,,$(cf:.c=.o))) >> $@))

$(OBJS): $(OBJOUT)/%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

-include $(DEPFILE)

clean:
	find $(OBJOUT) -name *.o | xargs rm -f
	rm -f $(DEPFILE)
	rm -f lkxsample
