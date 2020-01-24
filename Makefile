BUILDDIR := build
PRODUCT := solve_anagram
SRCDIR := src

HDRS := $(wildcard $(SRCDIR)/*.h)

CSRCS := $(wildcard $(SRCDIR)/*.cpp)

OBJS := $(CSRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

BINARY := $(BUILDDIR)/$(PRODUCT)

CXX := g++-9
CXXFLAGS_DEBUG := -g -DDEBUG
LD := $(CXX)

all : $(BINARY)

$(BINARY) : $(OBJS)
	@echo linking $@
	$(maketargetdir)
	$(LD) -o $@ $^

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@echo compiling $<
	$(maketargetdir)
	$(CXX) -c -o $@ $<

define maketargetdir
	-@mkdir -p $(dir $@) > /dev/null 2>&1
endef

clean :
	rm -f $(BINARY) $(OBJS)
	rm -rf $(BUILDDIR)
