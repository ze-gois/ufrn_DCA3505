# Makefile for ptrace-based deadlock detection tool
# Improved version with enhanced features

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2 -D_GNU_SOURCE
LDFLAGS = -pthread
TARGET = ptrace-lockdep

# Check for libelf availability
LIBELF_AVAILABLE := $(shell pkg-config --exists libelf && echo yes || echo no)
ifeq ($(LIBELF_AVAILABLE),yes)
    CFLAGS += -DHAVE_LIBELF $(shell pkg-config --cflags libelf)
    LDFLAGS += $(shell pkg-config --libs libelf)
    $(info Found libelf: enhanced symbol resolution enabled)
else
    $(info libelf not found: using fallback symbol resolution)
endif
SRCDIR = .
INCDIR = ../include
OBJDIR = obj
GRAPHDIR = ../graph
LIBDIR = ../../build

# Source files
SOURCES = main.c \
          ptrace_attach.c \
          syscall_intercept.c \
          pthread_structures.c \
          lock_tracker.c \
          backtrace.c

# Object files
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Dependencies
DEPS = $(OBJECTS:.o=.d)

# Include directories
INCLUDES = -I$(INCDIR) -I.

# Default target
all: $(TARGET)

# Create object directory
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Build target
$(TARGET): $(OBJDIR) $(OBJECTS) $(LIBDIR)/libgraph.a
	@echo "Linking $(TARGET)..."
	$(CC) $(OBJECTS) $(LIBDIR)/libgraph.a $(LDFLAGS) -o $(TARGET)
	@echo "Build complete: $(TARGET)"

# Compile source files
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Build the graph library if it doesn't exist
$(LIBDIR)/libgraph.a:
	@echo "Building graph library..."
	mkdir -p $(LIBDIR)
	$(MAKE) -C $(GRAPHDIR)
	$(MAKE) -C $(GRAPHDIR) install OUTDIR=../../build

# Install target (requires root for ptrace permissions)
install: $(TARGET)
	@echo "Installing $(TARGET)..."
	sudo cp $(TARGET) /usr/local/bin/
	sudo chmod u+s /usr/local/bin/$(TARGET)
	@echo "Installation complete. $(TARGET) installed to /usr/local/bin/"
	@echo "Note: The binary has been given setuid permissions for ptrace access."

# Uninstall target
uninstall:
	@echo "Uninstalling $(TARGET)..."
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstall complete."

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(OBJDIR)
	rm -f $(TARGET)
	@echo "Clean complete."

# Clean everything including dependencies
distclean: clean
	$(MAKE) -C $(GRAPHDIR) clean
	rm -f $(LIBDIR)/libgraph.a

# Run basic tests
test: $(TARGET)
	@echo "Running basic tests..."
	@echo "Testing help output..."
	./$(TARGET) --help
	@echo "Testing invalid PID..."
	./$(TARGET) 99999 || true
	@echo "Basic tests complete."

# Check for required dependencies
check-deps:
	@echo "Checking dependencies..."
	@which gcc > /dev/null || (echo "Error: gcc not found" && exit 1)
	@echo "Required dependencies satisfied."
	@echo "Optional dependencies:"
	@pkg-config --exists libelf && echo "  ✓ libelf found (enhanced symbol resolution)" || echo "  ✗ libelf not found (fallback mode will be used)"

# Debug build
debug: CFLAGS += -DDEBUG -g3 -O0
debug: $(TARGET)

# Release build
release: CFLAGS += -DNDEBUG -O3 -s
release: $(TARGET)

# Profile build
profile: CFLAGS += -pg -fprofile-arcs -ftest-coverage
profile: LDFLAGS += -pg -lgcov
profile: $(TARGET)

# Static analysis with cppcheck
analyze:
	@echo "Running static analysis..."
	@which cppcheck > /dev/null || (echo "Warning: cppcheck not found, skipping analysis" && exit 0)
	cppcheck --enable=all --std=c99 --platform=unix64 $(INCLUDES) $(SOURCES)

# Format code with clang-format
format:
	@echo "Formatting code..."
	@which clang-format > /dev/null || (echo "Warning: clang-format not found, skipping formatting" && exit 0)
	clang-format -i -style="{BasedOnStyle: Linux, IndentWidth: 4, TabWidth: 4, UseTab: Never}" $(SOURCES) *.h

# Generate documentation
docs:
	@echo "Generating documentation..."
	@which doxygen > /dev/null || (echo "Warning: doxygen not found, skipping documentation" && exit 0)
	doxygen Doxyfile 2>/dev/null || echo "Doxygen configuration not found, skipping..."

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Build the ptrace-lockdep tool (default)"
	@echo "  install   - Install the tool to /usr/local/bin (requires sudo)"
	@echo "  uninstall - Remove the tool from /usr/local/bin"
	@echo "  clean     - Remove build artifacts"
	@echo "  distclean - Remove all build artifacts including dependencies"
	@echo "  test      - Run basic functionality tests"
	@echo "  check-deps- Check for required dependencies"
	@echo "  debug     - Build with debug flags"
	@echo "  release   - Build optimized release version"
	@echo "  profile   - Build with profiling support"
	@echo "  analyze   - Run static code analysis"
	@echo "  format    - Format source code"
	@echo "  docs      - Generate documentation"
	@echo "  help      - Show this help message"

# Mark phony targets
.PHONY: all install uninstall clean distclean test check-deps debug release profile analyze format docs help

# Include dependency files
-include $(DEPS)

# Compilation database for IDE support
compile_commands.json: clean
	@echo "Generating compilation database..."
	bear -- make all

# Package for distribution
package: clean
	@echo "Creating distribution package..."
	tar -czf ptrace-lockdep-$(shell date +%Y%m%d).tar.gz \
		*.c *.h Makefile README.md LICENSE 2>/dev/null || \
		tar -czf ptrace-lockdep-$(shell date +%Y%m%d).tar.gz *.c *.h Makefile

# Show build information
info:
	@echo "Build Information:"
	@echo "  Compiler: $(CC)"
	@echo "  CFLAGS: $(CFLAGS)"
	@echo "  LDFLAGS: $(LDFLAGS)"
	@echo "  Sources: $(SOURCES)"
	@echo "  Target: $(TARGET)"
	@echo "  Object dir: $(OBJDIR)"
	@echo "  libelf support: $(LIBELF_AVAILABLE)"

# Rebuild everything
rebuild: clean all

# Quick build (skip dependency checks)
quick:
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) $(LIBDIR)/libgraph.a $(LDFLAGS) -o $(TARGET)
