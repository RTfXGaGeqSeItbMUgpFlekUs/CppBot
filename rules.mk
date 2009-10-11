OBJS= $(subst .cpp,.o,$(SRCS))

ifeq ($(TYPE),bin)
all: deps $(BIN)
endif

ifeq ($(TYPE),lib)
all: deps $(LIB)
endif

deps:
	@$(foreach DEP,$(DEPS),echo "     DEP $(DEP)"; (cd $(DEP); make);)

options:
	@echo "PREFIX   = $(PREFIX)"
	@echo "CC       = $(CC)"
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "CXX      = $(CXX)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
	@echo "LD       = $(LD)"
	@echo "LDFLAGS  = $(LDFLAGS)"
	@echo "SRCS     = $(SRCS)"
	@echo "OBJS     = $(OBJS)"

$(BIN): $(OBJS)
	@echo "    LINK $@"
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

$(LIB): $(OBJS)
	@echo "    LINK $@"
	@$(AR) $(ARFLAGS) rcs $@ $(OBJS)

%.o: %.c
	@echo "      CC $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

%.o: %.cpp
	@echo "      CC $@"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

ifneq ($(TYPE),global)
clean:
	@echo "   CLEAN"
	-@rm $(BIN) $(LIB) $(OBJS)
endif

.PHONY: all options clean
