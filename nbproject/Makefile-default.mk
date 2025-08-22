#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/PIC32MZ_UAC2_8CH_OUTPUT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/PIC32MZ_UAC2_8CH_OUTPUT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/app/main.c src/app/system.c src/drivers/usb/usb_LL.c src/drivers/usb/usb_PL.c src/drivers/i2s/i2s.c src/drivers/port/port.c src/drivers/tmr/tmr.c src/drivers/dma/dma.c src/drivers/clk/clk.c src/drivers/uart/uart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app/main.o ${OBJECTDIR}/src/app/system.o ${OBJECTDIR}/src/drivers/usb/usb_LL.o ${OBJECTDIR}/src/drivers/usb/usb_PL.o ${OBJECTDIR}/src/drivers/i2s/i2s.o ${OBJECTDIR}/src/drivers/port/port.o ${OBJECTDIR}/src/drivers/tmr/tmr.o ${OBJECTDIR}/src/drivers/dma/dma.o ${OBJECTDIR}/src/drivers/clk/clk.o ${OBJECTDIR}/src/drivers/uart/uart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app/main.o.d ${OBJECTDIR}/src/app/system.o.d ${OBJECTDIR}/src/drivers/usb/usb_LL.o.d ${OBJECTDIR}/src/drivers/usb/usb_PL.o.d ${OBJECTDIR}/src/drivers/i2s/i2s.o.d ${OBJECTDIR}/src/drivers/port/port.o.d ${OBJECTDIR}/src/drivers/tmr/tmr.o.d ${OBJECTDIR}/src/drivers/dma/dma.o.d ${OBJECTDIR}/src/drivers/clk/clk.o.d ${OBJECTDIR}/src/drivers/uart/uart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app/main.o ${OBJECTDIR}/src/app/system.o ${OBJECTDIR}/src/drivers/usb/usb_LL.o ${OBJECTDIR}/src/drivers/usb/usb_PL.o ${OBJECTDIR}/src/drivers/i2s/i2s.o ${OBJECTDIR}/src/drivers/port/port.o ${OBJECTDIR}/src/drivers/tmr/tmr.o ${OBJECTDIR}/src/drivers/dma/dma.o ${OBJECTDIR}/src/drivers/clk/clk.o ${OBJECTDIR}/src/drivers/uart/uart.o

# Source Files
SOURCEFILES=src/app/main.c src/app/system.c src/drivers/usb/usb_LL.c src/drivers/usb/usb_PL.c src/drivers/i2s/i2s.c src/drivers/port/port.c src/drivers/tmr/tmr.c src/drivers/dma/dma.c src/drivers/clk/clk.c src/drivers/uart/uart.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/PIC32MZ_UAC2_8CH_OUTPUT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ1024EFG064
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/app/main.o: src/app/main.c  .generated_files/flags/default/e0978e8225bfe71cb1a5f1e3aec52dbe7111eb05 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/main.o.d 
	@${RM} ${OBJECTDIR}/src/app/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/app/main.o.d" -o ${OBJECTDIR}/src/app/main.o src/app/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/system.o: src/app/system.c  .generated_files/flags/default/22e4a381b41ff67681401ef371fb32f107182718 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/system.o.d 
	@${RM} ${OBJECTDIR}/src/app/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/app/system.o.d" -o ${OBJECTDIR}/src/app/system.o src/app/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/usb/usb_LL.o: src/drivers/usb/usb_LL.c  .generated_files/flags/default/faf4d31ad70c208cf44ceabb3655b7ce4c134113 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/usb" 
	@${RM} ${OBJECTDIR}/src/drivers/usb/usb_LL.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/usb/usb_LL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/usb/usb_LL.o.d" -o ${OBJECTDIR}/src/drivers/usb/usb_LL.o src/drivers/usb/usb_LL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/usb/usb_PL.o: src/drivers/usb/usb_PL.c  .generated_files/flags/default/230b1a1f5f704b54be50ec6d71ea388b00f7811f .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/usb" 
	@${RM} ${OBJECTDIR}/src/drivers/usb/usb_PL.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/usb/usb_PL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/usb/usb_PL.o.d" -o ${OBJECTDIR}/src/drivers/usb/usb_PL.o src/drivers/usb/usb_PL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/i2s/i2s.o: src/drivers/i2s/i2s.c  .generated_files/flags/default/ce629edb6a73013454e7c4a50519ef8392b71a36 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/i2s" 
	@${RM} ${OBJECTDIR}/src/drivers/i2s/i2s.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/i2s/i2s.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/i2s/i2s.o.d" -o ${OBJECTDIR}/src/drivers/i2s/i2s.o src/drivers/i2s/i2s.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/port/port.o: src/drivers/port/port.c  .generated_files/flags/default/56999089f872b3cdef895670608064d66ba01842 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/port" 
	@${RM} ${OBJECTDIR}/src/drivers/port/port.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/port/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/port/port.o.d" -o ${OBJECTDIR}/src/drivers/port/port.o src/drivers/port/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/tmr/tmr.o: src/drivers/tmr/tmr.c  .generated_files/flags/default/75fd4678b8cf5668b04ebd35940f4ec4c29dcf9a .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/tmr" 
	@${RM} ${OBJECTDIR}/src/drivers/tmr/tmr.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/tmr/tmr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/tmr/tmr.o.d" -o ${OBJECTDIR}/src/drivers/tmr/tmr.o src/drivers/tmr/tmr.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/dma/dma.o: src/drivers/dma/dma.c  .generated_files/flags/default/d44825901f42ac732772490afdb204ffc4a100e0 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/dma" 
	@${RM} ${OBJECTDIR}/src/drivers/dma/dma.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/dma/dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/dma/dma.o.d" -o ${OBJECTDIR}/src/drivers/dma/dma.o src/drivers/dma/dma.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/clk/clk.o: src/drivers/clk/clk.c  .generated_files/flags/default/deadc34e39377004e1b40721de44d73edd558325 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/clk" 
	@${RM} ${OBJECTDIR}/src/drivers/clk/clk.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/clk/clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/clk/clk.o.d" -o ${OBJECTDIR}/src/drivers/clk/clk.o src/drivers/clk/clk.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/uart/uart.o: src/drivers/uart/uart.c  .generated_files/flags/default/522162ee4b08d53d1ebe44f15f4a0347094f7edb .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/uart" 
	@${RM} ${OBJECTDIR}/src/drivers/uart/uart.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/uart/uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/uart/uart.o.d" -o ${OBJECTDIR}/src/drivers/uart/uart.o src/drivers/uart/uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/src/app/main.o: src/app/main.c  .generated_files/flags/default/96778e121f13846e42c85f3e0f836618a71cefb4 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/main.o.d 
	@${RM} ${OBJECTDIR}/src/app/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/app/main.o.d" -o ${OBJECTDIR}/src/app/main.o src/app/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/system.o: src/app/system.c  .generated_files/flags/default/c03e56df3047cfb10145c7455f315eaba23c29ff .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/system.o.d 
	@${RM} ${OBJECTDIR}/src/app/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/app/system.o.d" -o ${OBJECTDIR}/src/app/system.o src/app/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/usb/usb_LL.o: src/drivers/usb/usb_LL.c  .generated_files/flags/default/a4cb42fdf27d088f96828bbcc34ef51c475b73f9 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/usb" 
	@${RM} ${OBJECTDIR}/src/drivers/usb/usb_LL.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/usb/usb_LL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/usb/usb_LL.o.d" -o ${OBJECTDIR}/src/drivers/usb/usb_LL.o src/drivers/usb/usb_LL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/usb/usb_PL.o: src/drivers/usb/usb_PL.c  .generated_files/flags/default/ecc45b22cf3b885ea51787ae52b961eb701f2906 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/usb" 
	@${RM} ${OBJECTDIR}/src/drivers/usb/usb_PL.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/usb/usb_PL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/usb/usb_PL.o.d" -o ${OBJECTDIR}/src/drivers/usb/usb_PL.o src/drivers/usb/usb_PL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/i2s/i2s.o: src/drivers/i2s/i2s.c  .generated_files/flags/default/7904e4c3f615c530b8b6701e2c5808d362e7e768 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/i2s" 
	@${RM} ${OBJECTDIR}/src/drivers/i2s/i2s.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/i2s/i2s.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/i2s/i2s.o.d" -o ${OBJECTDIR}/src/drivers/i2s/i2s.o src/drivers/i2s/i2s.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/port/port.o: src/drivers/port/port.c  .generated_files/flags/default/edeb4fa92f3f6c5c30575ae7a8b1211db1af92e3 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/port" 
	@${RM} ${OBJECTDIR}/src/drivers/port/port.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/port/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/port/port.o.d" -o ${OBJECTDIR}/src/drivers/port/port.o src/drivers/port/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/tmr/tmr.o: src/drivers/tmr/tmr.c  .generated_files/flags/default/b96200edc33adaf0cda2154236fbffe90bd38111 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/tmr" 
	@${RM} ${OBJECTDIR}/src/drivers/tmr/tmr.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/tmr/tmr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/tmr/tmr.o.d" -o ${OBJECTDIR}/src/drivers/tmr/tmr.o src/drivers/tmr/tmr.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/dma/dma.o: src/drivers/dma/dma.c  .generated_files/flags/default/708e97176ab80c4c49551a41cdff761655af26aa .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/dma" 
	@${RM} ${OBJECTDIR}/src/drivers/dma/dma.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/dma/dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/dma/dma.o.d" -o ${OBJECTDIR}/src/drivers/dma/dma.o src/drivers/dma/dma.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/clk/clk.o: src/drivers/clk/clk.c  .generated_files/flags/default/6537325ec1b6b28364e5f939fa8e4ab58650a4f3 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/clk" 
	@${RM} ${OBJECTDIR}/src/drivers/clk/clk.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/clk/clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/clk/clk.o.d" -o ${OBJECTDIR}/src/drivers/clk/clk.o src/drivers/clk/clk.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drivers/uart/uart.o: src/drivers/uart/uart.c  .generated_files/flags/default/9a695292c7bc4b0e212baaccb177126d540171e7 .generated_files/flags/default/c24b72d7bee263215258d3ef55fcfe58c1441450
	@${MKDIR} "${OBJECTDIR}/src/drivers/uart" 
	@${RM} ${OBJECTDIR}/src/drivers/uart/uart.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/uart/uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/uart/uart.o.d" -o ${OBJECTDIR}/src/drivers/uart/uart.o src/drivers/uart/uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/PIC32MZ_UAC2_8CH_OUTPUT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/PIC32MZ_UAC2_8CH_OUTPUT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=4096,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/PIC32MZ_UAC2_8CH_OUTPUT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/PIC32MZ_UAC2_8CH_OUTPUT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4096,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/PIC32MZ_UAC2_8CH_OUTPUT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
