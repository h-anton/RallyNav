# Helper macros to convert spaces into question marks and back again
e := 
sp := $(e) $(e)
qs = $(subst ?,$(sp),$1)
sq = $(subst $(sp),?,$1)

# Get name of this Makefile (avoid getting word 0 and a starting space)
makefile_name := $(wordlist 1,1000,$(MAKEFILE_LIST))

# Get path of this Makefile
makefile_path := $(call qs,$(dir $(call sq,$(abspath $(call sq,$(makefile_name))))))

# Get path where the Application is
application_path := $(call qs,$(abspath $(call sq,$(makefile_path)../..)))

.PHONY: clean assets all

ifneq ($(words $(makefile_path))$(words $(MAKEFILE_LIST)),11)
all clean assets:
$(error Spaces not allowed in path)
else

ADDITIONAL_SOURCES := 
ADDITIONAL_INCLUDE_PATHS := libraries/libosmscout/libosmscout/include libraries/libosmscout/libosmscout-map/include build/libraries/libosmscout/libosmscout/include build/libraries/libosmscout/libosmscout-map/include
ADDITIONAL_LIBRARY_PATHS := lib
ADDITIONAL_LIBRARIES := iconv osmscout osmscout_map
export ADDITIONAL_SOURCES ADDITIONAL_INCLUDE_PATHS ADDITIONAL_LIBRARY_PATHS ADDITIONAL_LIBRARIES

all: build-libraries $(filter assets,$(MAKECMDGOALS))
all assets: $(filter clean,$(MAKECMDGOALS))
all clean assets:
	@$(MAKE) -r -f generated/simulator/gcc/Makefile -s $(MFLAGS) $@ -C "$(application_path)"
endif

build-libraries: lib/libosmscout.a lib/libosmscout_map.a build/bin/libosmscout.dll build/bin/libosmscout_map.dll build/bin/libiconv-2.dll

lib/libosmscout.a lib/libosmscout_map.a build/bin/libosmscout.dll build/bin/libosmscout_map.dll build/bin/libiconv-2.dll:
	-mkdir -p build/libraries/libosmscout
	-mkdir -p build/bin
	cd build/libraries/libosmscout \
	&& cmake \
		-G "MSYS Makefiles" \
	    -DCMAKE_BUILD_TYPE=Release \
	    -DOSMSCOUT_BUILD_DEMOS=OFF \
	    -DOSMSCOUT_BUILD_TOOL_DUMPDATA=OFF \
	    -DOSMSCOUT_BUILD_TOOL_IMPORT=OFF \
	    -DOSMSCOUT_BUILD_GPX=OFF \
	    -DOSMSCOUT_BUILD_TOOL_PUBLICTRANSPORTMAP=OFF \
	    -DOSMSCOUT_BUILD_TESTS=OFF \
	../../../libraries/libosmscout \
	&& make -j8
	cp build/libraries/libosmscout/libosmscout/libosmscout.dll.a lib/libosmscout.a
	cp build/libraries/libosmscout/libosmscout-map/libosmscout_map.dll.a lib/libosmscout_map.a
	cp build/libraries/libosmscout/libosmscout/libosmscout.dll build/bin/libosmscout.dll
	cp build/libraries/libosmscout/libosmscout-map/libosmscout_map.dll build/bin/libosmscout_map.dll
	cp /mingw32/bin/libiconv-2.dll build/bin/libiconv-2.dll
