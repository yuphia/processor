STANDARD = -std=c++14 

WARNSF = -fpermissive -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address \
		 -fsanitize=bool -fsanitize=bounds -fsanitize=enum -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak\
		 -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift -fsanitize=signed-integer-overflow \
		 -fsanitize=undefined -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr -lm -pie #-fsanitize=alignment

WARNS =  -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported  -Wctor-dtor-privacy \
		 -Wempty-body -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlarger-than=128000 -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor \
		 -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-promo -Wstack-usage=16374 -Wstrict-null-sentinel -Wstrict-overflow=2 \
		 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code \
		 -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wall -Wextra -Wpedantic  \
		 -Wno-error=unused-function -Wsign-conversion #-Wconversion #-Wfloat-equal

ENABLE_WERROR = -Werror
ENABLE_PIE = -pie
ENABLE_GDB = -g

ENABLE_DEBUG = -D DEBUG_STK
DISABLE_DEBUG = -D NDEBUG_STK

NUM_ERRORS = -fmax-errors=1

SOURCES_ASM = ./assembler/assembler.cpp ./lib/StrFuncs/strlibMy.cpp ./lib/SortingAlg/sort.cpp ./lib/fileInput/fileInputTreatment.cpp ./assembler/assFunctions.cpp
SOURCES_DISASM = ./disassembler/disassembler.cpp ./lib/StrFuncs/strlibMy.cpp ./lib/SortingAlg/sort.cpp ./lib/fileInput/fileInputTreatment.cpp ./disassembler/disassemblerCmds.cpp
SOURCES_PROC   = ./processor/processor.cpp ./lib/StrFuncs/strlibMy.cpp ./lib/SortingAlg/sort.cpp ./lib/fileInput/fileInputTreatment.cpp ./processor/processorCmds.cpp ./lib/guard/ultimateGuard.cpp ./lib/stackFuncs/stackFunctions.cpp

DIRECTORIES = -I ./lib/SortingAlg/ -I ./lib/StrFuncs/ -I ./lib/fileInput/ -I ./lib/MistakeHandling/ -I ./lib/commands/ -I ./assembler -I ./disassembler -I ./processor -I ./lib/guard/ -I ./lib/stackFuncs/

FILES_FOR_ASM = assembler/examples/code.asm assembler/examples/asm.bin
FILES_FOR_DISASM = assembler/examples/asm.bin disassembler/examples/disasm.asm
FILES_FOR_PROC = assembler/examples/asm.bin

DIR_BUILD_ASM = buildAsm
DIR_RELEASE_ASM = $(DIR_BUILD_ASM)/release
DIR_DEBUG_ASM   = $(DIR_BUILD_ASM)/debug

OBJ_FILE_PATH_RELEASE_ASM = $(DIR_RELEASE_ASM)/assembler.out 
OBJECTS_RELEASE_ASM       = -o $(OBJ_FILE_PATH_RELEASE_ASM)

OBJ_FILE_PATH_DEBUG_ASM   = $(DIR_DEBUG_ASM)/assembler.out
OBJECTS_DEBUG_ASM         = -o $(OBJ_FILE_PATH_DEBUG_ASM)

DIR_BUILD_DISASM = buildDisasm
DIR_RELEASE_DISASM = $(DIR_BUILD_DISASM)/release
DIR_DEBUG_DISASM   = $(DIR_BUILD_DISASM)/debug

OBJ_FILE_PATH_RELEASE_DISASM = $(DIR_RELEASE_DISASM)/disassembler.out 
OBJECTS_RELEASE_DISASM       = -o $(OBJ_FILE_PATH_RELEASE_DISASM)

OBJ_FILE_PATH_DEBUG_DISASM   = $(DIR_DEBUG_DISASM)/disassembler.out
OBJECTS_DEBUG_DISASM         = -o $(OBJ_FILE_PATH_DEBUG_DISASM) 

DIR_BUILD_PROC = buildProc
DIR_RELEASE_PROC = $(DIR_BUILD_PROC)/release
DIR_DEBUG_PROC   = $(DIR_BUILD_PROC)/debug

OBJ_FILE_PATH_RELEASE_PROC = $(DIR_RELEASE_PROC)/disassembler.out 
OBJECTS_RELEASE_PROC       = -o $(OBJ_FILE_PATH_RELEASE_PROC)

OBJ_FILE_PATH_DEBUG_PROC   = $(DIR_DEBUG_PROC)/disassembler.out
OBJECTS_DEBUG_PROC         = -o $(OBJ_FILE_PATH_DEBUG_PROC) 

COMPILER = g++

all: releaseProc	

createLog:
	touch log.txt

releaseAsm:
	mkdir -p $(DIR_RELEASE_ASM)
	$(COMPILER) $(STANDARD) $(WARNS)                                                       $(DISABLE_DEBUG) $(DIRECTORIES) $(SOURCES_ASM) $(OBJECTS_RELEASE_ASM) 	

debugAsm:
	mkdir -p $(DIR_DEBUG_ASM)
	$(COMPILER) $(ENABLE_WERROR) $(ENABLE_GDB) $(STANDARD) $(WARNS) $(WARNSF) $(ENABLE_PIE) $(ENABLE_DEBUG) $(DIRECTORIES) $(SOURCES_ASM) $(OBJECTS_DEBUG_ASM) $(NUM_ERRORS)

cleanAsm:
	rm -rf $(DIR_BUILD_ASM)/*

runAsm:
	./$(OBJ_FILE_PATH_RELEASE_ASM) $(FILES_FOR_ASM)

runNameAsm:
	./$(OBJ_FILE_PATH_RELEASE_ASM) 

rundbgAsm:
	./$(OBJ_FILE_PATH_DEBUG_ASM)   $(FILES_FOR_ASM)

rundbgAsmName:
	./$(OBJ_FILE_PATH_DEBUG_ASM) 

releaseDisasm:
	mkdir -p $(DIR_RELEASE_DISASM)
	$(COMPILER) $(STANDARD) $(WARNS)                                                       $(DISABLE_DEBUG) $(DIRECTORIES) $(SOURCES_DISASM) $(OBJECTS_RELEASE_DISASM) 	

debugDisasm:
	mkdir -p $(DIR_DEBUG_DISASM)
	$(COMPILER) $(ENABLE_WERROR) $(ENABLE_GDB) $(STANDARD) $(WARNS) $(WARNSF) $(ENABLE_PIE) $(ENABLE_DEBUG) $(DIRECTORIES) $(SOURCES_DISASM) $(OBJECTS_DEBUG_DISASM) $(NUM_ERRORS)

cleanDisasm:
	rm -rf $(DIR_BUILD_DISASM)/*

runDisasm:
	./$(OBJ_FILE_PATH_RELEASE_DISASM) $(FILES_FOR_DISASM)

runNameDisasm:
	./$(OBJ_FILE_PATH_RELEASE_DISASM) 

rundbgDisasm:
	./$(OBJ_FILE_PATH_DEBUG_DISASM)   $(FILES_FOR_DISASM)

rundbgNameDisasm:
	./$(OBJ_FILE_PATH_DEBUG_DISASM)

releaseProc:
	mkdir -p $(DIR_RELEASE_PROC)
	$(COMPILER) $(STANDARD) $(WARNS)                                                       $(DISABLE_DEBUG) $(DIRECTORIES) $(SOURCES_PROC) $(OBJECTS_RELEASE_PROC) 	

debugProc:
	mkdir -p $(DIR_DEBUG_PROC)
	$(COMPILER) $(ENABLE_WERROR) $(ENABLE_GDB) $(STANDARD) $(WARNS) $(WARNSF) $(ENABLE_PIE) $(ENABLE_DEBUG) $(DIRECTORIES) $(SOURCES_PROC) $(OBJECTS_DEBUG_PROC) $(NUM_ERRORS)

cleanProc:
	rm -rf $(DIR_BUILD_PROC)/*

runProc:
	./$(OBJ_FILE_PATH_RELEASE_PROC) $(FILES_FOR_PROC)

runNameProc:
	./$(OBJ_FILE_PATH_RELEASE_PROC) 

rundbgProc:
	./$(OBJ_FILE_PATH_DEBUG_PROC)   $(FILES_FOR_PROC)

rundbgNameProc:
	./$(OBJ_FILE_PATH_DEBUG_PROC)

openCode:
	vim assembler/examples/code.asm

openAsm:
	ghex assembler/examples/asm.bin

openDisasm:
	vim disassembler/examples/disasm.asm

openSquare:
	vim assembler/examples/square.asm

asmSquare:
	./$(OBJ_FILE_PATH_RELEASE_ASM) assembler/examples/square.asm assembler/examples/square.bin

runSquare:
	./$(OBJ_FILE_PATH_RELEASE_PROC)  assembler/examples/square.bin

disasmSquare:
	./$(OBJ_FILE_PATH_RELEASE_DISASM) assembler/examples/square.bin disassembler/examples/squareDis.asm

opAsmSquare:
	ghex assembler/examples/square.bin

opDisSquare:
	vim disassembler/examples/squareDis.asm




