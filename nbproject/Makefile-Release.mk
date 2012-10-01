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
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/sensor_factory.o \
	${OBJECTDIR}/json_formatter.o \
	${OBJECTDIR}/water_sensor.o \
	${OBJECTDIR}/url_loader.o \
	${OBJECTDIR}/logger.o \
	${OBJECTDIR}/message_type.o \
	${OBJECTDIR}/jsmn.o \
	${OBJECTDIR}/alarm.o \
	${OBJECTDIR}/communication.o \
	${OBJECTDIR}/reading_data.o \
	${OBJECTDIR}/sensor_type.o \
	${OBJECTDIR}/time_functions.o \
	${OBJECTDIR}/queue.o \
	${OBJECTDIR}/StringBuffer.o \
	${OBJECTDIR}/linked_list.o \
	${OBJECTDIR}/mock_sensor.o \
	${OBJECTDIR}/battery_sensor.o \
	${OBJECTDIR}/sensor.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/json_parser.o \
	${OBJECTDIR}/sprinkler.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Llibcurl -lcurl

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/sensor_factory.o: sensor_factory.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/sensor_factory.o sensor_factory.c

${OBJECTDIR}/json_formatter.o: json_formatter.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/json_formatter.o json_formatter.c

${OBJECTDIR}/water_sensor.o: water_sensor.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/water_sensor.o water_sensor.c

${OBJECTDIR}/url_loader.o: url_loader.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/url_loader.o url_loader.c

${OBJECTDIR}/logger.o: logger.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/logger.o logger.c

${OBJECTDIR}/message_type.o: message_type.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/message_type.o message_type.c

${OBJECTDIR}/jsmn.o: jsmn.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/jsmn.o jsmn.c

${OBJECTDIR}/alarm.o: alarm.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/alarm.o alarm.c

${OBJECTDIR}/communication.o: communication.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/communication.o communication.c

${OBJECTDIR}/reading_data.o: reading_data.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/reading_data.o reading_data.c

${OBJECTDIR}/sensor_type.o: sensor_type.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/sensor_type.o sensor_type.c

${OBJECTDIR}/time_functions.o: time_functions.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/time_functions.o time_functions.c

${OBJECTDIR}/queue.o: queue.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/queue.o queue.c

${OBJECTDIR}/StringBuffer.o: StringBuffer.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/StringBuffer.o StringBuffer.c

${OBJECTDIR}/linked_list.o: linked_list.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/linked_list.o linked_list.c

${OBJECTDIR}/mock_sensor.o: mock_sensor.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/mock_sensor.o mock_sensor.c

${OBJECTDIR}/battery_sensor.o: battery_sensor.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/battery_sensor.o battery_sensor.c

${OBJECTDIR}/sensor.o: sensor.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/sensor.o sensor.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/json_parser.o: json_parser.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/json_parser.o json_parser.c

${OBJECTDIR}/sprinkler.o: sprinkler.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/sprinkler.o sprinkler.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/alarm_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/check_communication.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/check_json_parser.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/checklogger.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/check_url_loader.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/linked_link_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/string_buffer_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/test_json_formatter.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/test_queue.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/test_sensor.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler: ${TESTDIR}/tests/test_sprinkler.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/alarm_test.o: tests/alarm_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/alarm_test.o tests/alarm_test.c


${TESTDIR}/tests/check_communication.o: tests/check_communication.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/check_communication.o tests/check_communication.c


${TESTDIR}/tests/check_json_parser.o: tests/check_json_parser.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/check_json_parser.o tests/check_json_parser.c


${TESTDIR}/tests/checklogger.o: tests/checklogger.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/checklogger.o tests/checklogger.c


${TESTDIR}/tests/check_url_loader.o: tests/check_url_loader.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/check_url_loader.o tests/check_url_loader.c


${TESTDIR}/tests/linked_link_test.o: tests/linked_link_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/linked_link_test.o tests/linked_link_test.c


${TESTDIR}/tests/string_buffer_test.o: tests/string_buffer_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/string_buffer_test.o tests/string_buffer_test.c


${TESTDIR}/tests/test_json_formatter.o: tests/test_json_formatter.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/test_json_formatter.o tests/test_json_formatter.c


${TESTDIR}/tests/test_queue.o: tests/test_queue.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/test_queue.o tests/test_queue.c


${TESTDIR}/tests/test_sensor.o: tests/test_sensor.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/test_sensor.o tests/test_sensor.c


${TESTDIR}/tests/test_sprinkler.o: tests/test_sprinkler.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/test_sprinkler.o tests/test_sprinkler.c


${OBJECTDIR}/sensor_factory_nomain.o: ${OBJECTDIR}/sensor_factory.o sensor_factory.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/sensor_factory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/sensor_factory_nomain.o sensor_factory.c;\
	else  \
	    ${CP} ${OBJECTDIR}/sensor_factory.o ${OBJECTDIR}/sensor_factory_nomain.o;\
	fi

${OBJECTDIR}/json_formatter_nomain.o: ${OBJECTDIR}/json_formatter.o json_formatter.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/json_formatter.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/json_formatter_nomain.o json_formatter.c;\
	else  \
	    ${CP} ${OBJECTDIR}/json_formatter.o ${OBJECTDIR}/json_formatter_nomain.o;\
	fi

${OBJECTDIR}/water_sensor_nomain.o: ${OBJECTDIR}/water_sensor.o water_sensor.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/water_sensor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/water_sensor_nomain.o water_sensor.c;\
	else  \
	    ${CP} ${OBJECTDIR}/water_sensor.o ${OBJECTDIR}/water_sensor_nomain.o;\
	fi

${OBJECTDIR}/url_loader_nomain.o: ${OBJECTDIR}/url_loader.o url_loader.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/url_loader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/url_loader_nomain.o url_loader.c;\
	else  \
	    ${CP} ${OBJECTDIR}/url_loader.o ${OBJECTDIR}/url_loader_nomain.o;\
	fi

${OBJECTDIR}/logger_nomain.o: ${OBJECTDIR}/logger.o logger.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/logger.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/logger_nomain.o logger.c;\
	else  \
	    ${CP} ${OBJECTDIR}/logger.o ${OBJECTDIR}/logger_nomain.o;\
	fi

${OBJECTDIR}/message_type_nomain.o: ${OBJECTDIR}/message_type.o message_type.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/message_type.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/message_type_nomain.o message_type.c;\
	else  \
	    ${CP} ${OBJECTDIR}/message_type.o ${OBJECTDIR}/message_type_nomain.o;\
	fi

${OBJECTDIR}/jsmn_nomain.o: ${OBJECTDIR}/jsmn.o jsmn.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/jsmn.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/jsmn_nomain.o jsmn.c;\
	else  \
	    ${CP} ${OBJECTDIR}/jsmn.o ${OBJECTDIR}/jsmn_nomain.o;\
	fi

${OBJECTDIR}/alarm_nomain.o: ${OBJECTDIR}/alarm.o alarm.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alarm.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/alarm_nomain.o alarm.c;\
	else  \
	    ${CP} ${OBJECTDIR}/alarm.o ${OBJECTDIR}/alarm_nomain.o;\
	fi

${OBJECTDIR}/communication_nomain.o: ${OBJECTDIR}/communication.o communication.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/communication.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/communication_nomain.o communication.c;\
	else  \
	    ${CP} ${OBJECTDIR}/communication.o ${OBJECTDIR}/communication_nomain.o;\
	fi

${OBJECTDIR}/reading_data_nomain.o: ${OBJECTDIR}/reading_data.o reading_data.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/reading_data.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/reading_data_nomain.o reading_data.c;\
	else  \
	    ${CP} ${OBJECTDIR}/reading_data.o ${OBJECTDIR}/reading_data_nomain.o;\
	fi

${OBJECTDIR}/sensor_type_nomain.o: ${OBJECTDIR}/sensor_type.o sensor_type.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/sensor_type.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/sensor_type_nomain.o sensor_type.c;\
	else  \
	    ${CP} ${OBJECTDIR}/sensor_type.o ${OBJECTDIR}/sensor_type_nomain.o;\
	fi

${OBJECTDIR}/time_functions_nomain.o: ${OBJECTDIR}/time_functions.o time_functions.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/time_functions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/time_functions_nomain.o time_functions.c;\
	else  \
	    ${CP} ${OBJECTDIR}/time_functions.o ${OBJECTDIR}/time_functions_nomain.o;\
	fi

${OBJECTDIR}/queue_nomain.o: ${OBJECTDIR}/queue.o queue.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/queue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/queue_nomain.o queue.c;\
	else  \
	    ${CP} ${OBJECTDIR}/queue.o ${OBJECTDIR}/queue_nomain.o;\
	fi

${OBJECTDIR}/StringBuffer_nomain.o: ${OBJECTDIR}/StringBuffer.o StringBuffer.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/StringBuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/StringBuffer_nomain.o StringBuffer.c;\
	else  \
	    ${CP} ${OBJECTDIR}/StringBuffer.o ${OBJECTDIR}/StringBuffer_nomain.o;\
	fi

${OBJECTDIR}/linked_list_nomain.o: ${OBJECTDIR}/linked_list.o linked_list.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/linked_list.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/linked_list_nomain.o linked_list.c;\
	else  \
	    ${CP} ${OBJECTDIR}/linked_list.o ${OBJECTDIR}/linked_list_nomain.o;\
	fi

${OBJECTDIR}/mock_sensor_nomain.o: ${OBJECTDIR}/mock_sensor.o mock_sensor.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/mock_sensor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/mock_sensor_nomain.o mock_sensor.c;\
	else  \
	    ${CP} ${OBJECTDIR}/mock_sensor.o ${OBJECTDIR}/mock_sensor_nomain.o;\
	fi

${OBJECTDIR}/battery_sensor_nomain.o: ${OBJECTDIR}/battery_sensor.o battery_sensor.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/battery_sensor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/battery_sensor_nomain.o battery_sensor.c;\
	else  \
	    ${CP} ${OBJECTDIR}/battery_sensor.o ${OBJECTDIR}/battery_sensor_nomain.o;\
	fi

${OBJECTDIR}/sensor_nomain.o: ${OBJECTDIR}/sensor.o sensor.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/sensor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/sensor_nomain.o sensor.c;\
	else  \
	    ${CP} ${OBJECTDIR}/sensor.o ${OBJECTDIR}/sensor_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.c;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/json_parser_nomain.o: ${OBJECTDIR}/json_parser.o json_parser.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/json_parser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/json_parser_nomain.o json_parser.c;\
	else  \
	    ${CP} ${OBJECTDIR}/json_parser.o ${OBJECTDIR}/json_parser_nomain.o;\
	fi

${OBJECTDIR}/sprinkler_nomain.o: ${OBJECTDIR}/sprinkler.o sprinkler.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/sprinkler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/sprinkler_nomain.o sprinkler.c;\
	else  \
	    ${CP} ${OBJECTDIR}/sprinkler.o ${OBJECTDIR}/sprinkler_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sprinkler

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
