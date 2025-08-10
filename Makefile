CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -O0 -g
LDFLAGS = -s -static

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

TARGET = $(BINDIR)/VELT

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

clean:
	$(RM) -rf $(OBJDIR) $(BINDIR)

run: $(TARGET)
	$(TARGET) file.txt

help:
	@echo Available targets:
	@echo   all     - Build the project
	@echo   clean   - Remove build artifacts
	@echo   run     - Build and run the program