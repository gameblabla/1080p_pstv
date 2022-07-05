cmake_minimum_required(VERSION 2.8)

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_C_COMPILER "arm-vita-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-vita-eabi-g++")

project(HENkaku)

set(CMAKE_C_FLAGS "-Wl,-q -Wall -O3 -std=gnu99")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

include_directories(
)

link_directories(
	${CMAKE_CURRENT_BINARY_DIR}
)

if (NOT ${RELEASE})
	add_definitions(-DENABLE_LOGGING)
endif()

add_executable(1080p.elf
	main.c
)

target_link_libraries(1080p.elf
	taihenForKernel_stub
	SceLedForDriver_stub
	ScePowerForDriver_stub
	SceGpioForDriver_stub
	)

set_target_properties(1080p.elf
	PROPERTIES LINK_FLAGS "-nostdlib"
	COMPILE_FLAGS "-D__VITA_KERNEL__"
)

add_custom_target(1080p.skprx ALL
	COMMAND vita-elf-create -e ${CMAKE_SOURCE_DIR}/1080p.yml 1080p.elf 1080p.velf ${CMAKE_SOURCE_DIR}/taihen.json
	COMMAND vita-make-fself -c 1080p.velf 1080p.skprx
)
add_dependencies(1080p.skprx 1080p.elf)

add_custom_target(send
	COMMAND curl -T 1080p.skprx ftp://$(PSVITAIP):1337/ux0:/data/tai/
	DEPENDS 1080p.skprx
)
