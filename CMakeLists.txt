cmake_minimum_required (VERSION 3.14)

project(processorEmulator)

option (DEBUG "Debug mode on or off?" OFF)

set (
WARNS
-Wall
-Wextra
-Wpedantic
-Weffc++
-Werror
-Waggressive-loop-optimizations
-Wc++0x-compat
-Wc++11-compat
-Wc++14-compat
-Wcast-align
-Wcast-qual
-Wchar-subscripts
-Wconditionally-supported
# -Wconversion
-Wctor-dtor-privacy
-Wempty-body
# -Wfloat-equal
-Wformat-nonliteral
-Wformat-security
-Wformat-signedness
-Wformat=2
-Winline
-Wlarger-than=16384
-Wlogical-op
-Wmissing-declarations
-Wnon-virtual-dtor
-Wopenmp-simd
-Woverloaded-virtual
-Wpacked
-Wpointer-arith
-Wredundant-decls
-Wshadow
-Wsign-conversion
-Wsign-promo
-Wstack-usage=16384
-Wstrict-null-sentinel
-Wstrict-overflow=2
-Wsuggest-attribute=noreturn
-Wsuggest-final-methods
-Wsuggest-final-types
-Wsuggest-override
-Wswitch-default
-Wswitch-enum
-Wsync-nand
-Wundef
-Wunreachable-code
# -Wunused
-Wuseless-cast
-Wvariadic-macros
-Wno-literal-suffix
-Wno-missing-field-initializers
-Wno-narrowing
-Wno-old-style-cast
-Wno-varargs
-fcheck-new
-fstack-protector
-fstrict-overflow
-flto-odr-type-merging
-fno-omit-frame-pointer
)

set(
FLAGS 
-fsanitize=address
-fsanitize=alignment
-fsanitize=bool
-fsanitize=bounds
-fsanitize=enum
-fsanitize=float-cast-overflow
-fsanitize=float-divide-by-zero
-fsanitize=integer-divide-by-zero
-fsanitize=leak
-fsanitize=nonnull-attribute
-fsanitize=null
-fsanitize=object-size
-fsanitize=return
-fsanitize=returns-nonnull-attribute
-fsanitize=shift
-fsanitize=signed-integer-overflow
-fsanitize=undefined
-fsanitize=unreachable
-fsanitize=vla-bound
-fsanitize=vptr
-fsized-deallocation
)

add_subdirectory(source)
message (STATUS "Collected libs: ${LIBLIST}")

foreach(LIB ${LIBLIST})
    target_include_directories (${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)  
endforeach()

add_subdirectory(tools)
message (STATUS "Collected tools: ${TOOLS}")

foreach(TOOL ${TOOLS})
    target_include_directories (${TOOL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

    if (DEBUG)
        target_link_options (${TOOL} PRIVATE "${FLAGS}")
        target_compile_options (${TOOL} PRIVATE "${FLAGS}")
        target_compile_options (${TOOL} PRIVATE "-D DEBUG")
    else()
        target_compile_options (${TOOL} PRIVATE "-D NDEBUG")
    endif() 

    target_compile_options (${TOOL} PRIVATE "${WARNS}")    
    target_compile_features(${TOOL} PRIVATE cxx_std_11)
    
    target_link_libraries(${TOOL} ${LIBLIST})
endforeach()
