set (
    LIBLIST
    assembler
    disassembler
    fileInputTreatment
    processor
    sort
    strlibMy
    stackFunctions
    ultimateGuard
)

foreach (LIB ${LIBLIST})
    add_subdirectory (${LIB})    
endforeach()

set (LIBLIST "${LIBLIST}" PARENT_SCOPE)
