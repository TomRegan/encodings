# This Makefile will delegate to the cmake generated Makefile
# in the build directory. Be sure to have run ./configure
# to generate this build before trying to run make from the
# project root.

BUILD_DIR := build
DOCS_DIR := doc
EXEC_DIR := $(BUILD_DIR)/src

.PHONY: all
all:
	$(MAKE) -C $(BUILD_DIR)/

.PHONY: test
test: all
	$(EXEC_DIR)/TestSuite

.PHONY: man
man:
	$(MAKE) -C $(DOCS_DIR)/

.PHONY: clean
clean:
	@$(MAKE) -C $(BUILD_DIR) clean

.PHONY: distclean
distclean:
	@echo Cleaning out $(BUILD_DIR)/
	@$(RM) -rf $(BUILD_DIR)/*

.PHONY: targets
targets:
	@echo "Makefile provides the following targets:\n"
	@echo "\tall\t\tbuild the application (default)"
	@echo "\ttest\t\trun unit tests"
	@echo "\tclean\t\tremove compiled files"
	@echo "\tdistclean\tremove files in $(BUILD_DIR) and $(DOCS_DIR)\n"
