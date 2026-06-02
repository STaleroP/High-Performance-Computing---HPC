#.SILENT:
.PHONY: release debug clean

CXX=g++
RM=rm -f
STRIP=strip
OUTPUT=example3
OBJS=example3.o

RELEASE_CPPFLAGS=-Wall -Wextra -pedantic -DNDEBUG
RELEASE_CXXFLAGS=-flto -O3
RELEASE_LDFLAGS=-flto

DEBUG_CPPFLAGS=-Wall -Wextra -pedantic
DEBUG_CXXFLAGS=-g
DEBUG_LDFLAGS=

release: CPPFLAGS=$(RELEASE_CPPFLAGS)
release: CXXFLAGS=$(RELEASE_CXXFLAGS)
release: LDFLAGS=$(RELEASE_LDFLAGS)
release: $(OUTPUT)
	$(STRIP) $(OUTPUT)

debug: CPPFLAGS=$(DEBUG_CPPFLAGS)
debug: CXXFLAGS=$(DEBUG_CXXFLAGS)
debug: LDFLAGS=$(DEBUG_LDFLAGS)
debug: $(OUTPUT)

clean:
	$(RM) $(OUTPUT) $(OBJS)

$(OUTPUT): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

example3.o: example3.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<
