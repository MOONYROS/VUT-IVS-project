#Root project folder relatively to makefile
PROJDIR := ..

#Directories in PROJDIR
DIRS := mockup profiling src	

#Executable and source files
EXEC := calculandumMachina
GUI_SRCS := main.cpp \
		mainwindow.cpp \
		mainwindow.h
MATLIB_SRCS := matlib.cpp \
				matlib.h

#Google tests executable
TESTS := matlib_tests

#Profiling files
PROFILE := $(PROJDIR)/profiling/stddeviation
PROFILE_SRC := $(PROFILE).cpp

#Final folder after pack command
PACK_DIR := xlukas15_xkouma02_xmorku03_xkonec85
PACK := $(PACK_DIR).zip

#Compilers and their flags
CC := gcc
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -Wpedantic

.PHONY : all pack clean test doc run profile installtest

all: profile
	sudo apt install qtbase5-dev -y
	mkdir build && cd build && cmake .. && make

pack: doc
	cd $(PROJDIR)/.. && mkdir $(PACK_DIR) && cd $(PACK_DIR) && mkdir doc install repo
	cp -r html latex $(PROJDIR)/../$(PACK_DIR)/doc
	cd $(PROJDIR)/.. && cp -r .git/ $(PACK_DIR)/repo
	cd $(PROJDIR)/.. && cp -r CalculandumMachina/* $(PACK_DIR)/repo && zip -rv $(PACK) $(PACK_DIR) && rm -rf $(PACK_DIR)

clean:
	cd $(PROJDIR) && ls | egrep -v 'mockup|plan|profiling|src|dokumentace.pdf|LICENSE|README.md|*.png|*.txt' | xargs rm -rf && rm -rf build-src-Desktop*
	ls | egrep -v 'main.cpp|mainwindow*|matlib*|Doxyfile|CMakeLists.txt|help.html|Makefile' | xargs rm -rf && rm -f *.o *.user matlib_tests
	cd $(PROJDIR)/profiling && ls | egrep -v '*.cpp|*.pdf' | xargs rm -rf
	cd $(PROJDIR)/mockup && ls | egrep -v 'mockup*' | xargs rm -rf
	cd $(PROJDIR)/plan && ls | egrep -v 'xlukas15*' | xargs rm -rf

# This part of Makefile is an edited version of
# GoogleTest official Makefile that is available on
# https://github.com/google/googletest/blob/release-1.8.1/googletest/make/Makefile
# (the link might get old by the time you're reading this)
GTEST_DIR := $(PROJDIR)/googletest/googletest

GTEST_HEADERS := $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS := $(GTEST_DIR)/src/*.cc \
			$(GTEST_DIR)/src/*.h \
			$(GTEST_HEADERS)
CPPFLAGS := -isystem $(GTEST_DIR)/include

installtest:
	cd $(PROJDIR) && git clone https://github.com/google/googletest/

test: $(TESTS)
	./$(TESTS)

$(TESTS): matlib.o $(TESTS).o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

matlib.o: $(MATLIB_SRCS) $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c matlib.cpp

$(TESTS).o: $(TESTS).cpp matlib.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TESTS).cpp

gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

gtest-all.o: $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) -I $(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) -I $(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a: gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(GTEST_HEADERS):
	$(error Google tests not found. Try "make installtest" and repeat.)
	
doc:
	doxygen Doxyfile

run:
	cd build && ./template

profile: $(PROFILE)

$(PROFILE): $(PROFILE_SRC) $(MATLIB_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@