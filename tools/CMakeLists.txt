
set(
    TOOLS
    assemblerExec
    disassemblerExec
    processorExec
)

foreach(TOOL ${TOOLS})
    add_subdirectory(${TOOL})    
endforeach()

set (TOOLS "${TOOLS}" PARENT_SCOPE)
