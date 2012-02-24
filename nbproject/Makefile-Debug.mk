#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/LinkedList.o \
	${OBJECTDIR}/Queue.o \
	${OBJECTDIR}/Simulation.o \
	${OBJECTDIR}/CommunicationProtocol.o \
	${OBJECTDIR}/Network-Topology.o \
	${OBJECTDIR}/FileOperations.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/distributed-chang-roberts-spanning-tree

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/distributed-chang-roberts-spanning-tree: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/distributed-chang-roberts-spanning-tree ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/LinkedList.o: nbproject/Makefile-${CND_CONF}.mk LinkedList.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/LinkedList.o LinkedList.c

${OBJECTDIR}/Queue.o: nbproject/Makefile-${CND_CONF}.mk Queue.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Queue.o Queue.c

${OBJECTDIR}/Simulation.o: nbproject/Makefile-${CND_CONF}.mk Simulation.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Simulation.o Simulation.c

${OBJECTDIR}/CommunicationProtocol.o: nbproject/Makefile-${CND_CONF}.mk CommunicationProtocol.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/CommunicationProtocol.o CommunicationProtocol.c

${OBJECTDIR}/Network-Topology.o: nbproject/Makefile-${CND_CONF}.mk Network-Topology.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Network-Topology.o Network-Topology.c

${OBJECTDIR}/FileOperations.o: nbproject/Makefile-${CND_CONF}.mk FileOperations.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/FileOperations.o FileOperations.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/TestCommunicationProtocol.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lcunit 


${TESTDIR}/tests/TestCommunicationProtocol.o: tests/TestCommunicationProtocol.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -s -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/TestCommunicationProtocol.o tests/TestCommunicationProtocol.c


${OBJECTDIR}/LinkedList_nomain.o: ${OBJECTDIR}/LinkedList.o LinkedList.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/LinkedList.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -s -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/LinkedList_nomain.o LinkedList.c;\
	else  \
	    ${CP} ${OBJECTDIR}/LinkedList.o ${OBJECTDIR}/LinkedList_nomain.o;\
	fi

${OBJECTDIR}/Queue_nomain.o: ${OBJECTDIR}/Queue.o Queue.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Queue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -s -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Queue_nomain.o Queue.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Queue.o ${OBJECTDIR}/Queue_nomain.o;\
	fi

${OBJECTDIR}/Simulation_nomain.o: ${OBJECTDIR}/Simulation.o Simulation.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Simulation.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -s -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Simulation_nomain.o Simulation.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Simulation.o ${OBJECTDIR}/Simulation_nomain.o;\
	fi

${OBJECTDIR}/CommunicationProtocol_nomain.o: ${OBJECTDIR}/CommunicationProtocol.o CommunicationProtocol.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CommunicationProtocol.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -s -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CommunicationProtocol_nomain.o CommunicationProtocol.c;\
	else  \
	    ${CP} ${OBJECTDIR}/CommunicationProtocol.o ${OBJECTDIR}/CommunicationProtocol_nomain.o;\
	fi

${OBJECTDIR}/Network-Topology_nomain.o: ${OBJECTDIR}/Network-Topology.o Network-Topology.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Network-Topology.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -s -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Network-Topology_nomain.o Network-Topology.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Network-Topology.o ${OBJECTDIR}/Network-Topology_nomain.o;\
	fi

${OBJECTDIR}/FileOperations_nomain.o: ${OBJECTDIR}/FileOperations.o FileOperations.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FileOperations.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -s -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/FileOperations_nomain.o FileOperations.c;\
	else  \
	    ${CP} ${OBJECTDIR}/FileOperations.o ${OBJECTDIR}/FileOperations_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/distributed-chang-roberts-spanning-tree

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
