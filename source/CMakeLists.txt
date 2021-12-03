set (
    LIBLIST
    fileInputTreatment
    sort
    strlibMy
    stackFunctions
    ultimateGuard
)

set (
    LIBSPROC
    processor
)

set (
    LIBSDISASM
    disassembler
)

set (
    LIBSASM
    assembler
)

foreach (LIB ${LIBLIST})
    add_subdirectory (${LIB})    
endforeach()

foreach (LIBPROC ${LIBSPROC})
    add_subdirectory (${LIBPROC})    
endforeach()

foreach (LIBASM ${LIBSASM})
    add_subdirectory (${LIBASM})    
endforeach()

foreach (LIBDISASM ${LIBSDISASM})
    add_subdirectory (${LIBDISASM})    
endforeach()

set (LIBLIST "${LIBLIST}" PARENT_SCOPE)
set (LIBSPROC "${LIBSPROC}" PARENT_SCOPE)
set (LIBSASM "${LIBSASM}" PARENT_SCOPE)
set (LIBSDISASM "${LIBSDISASM}" PARENT_SCOPE)
