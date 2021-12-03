set(
    TOOLS
    assembler
    disassembler
    processor
)

foreach(TOOL ${TOOLS})
    add_subdirectory(${TOOL})    
endforeach()

set (TOOLS "${TOOLS}" PARENT_SCOPE)