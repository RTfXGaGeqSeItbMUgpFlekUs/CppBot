TYPE= global
DEPS= libnetwork sockettest cppbot

include rules.mk

clean:
	@$(foreach DEP,$(DEPS),echo "  UNMAKE $(DEP)"; (cd $(DEP); make clean);)

.PHONY: clean
