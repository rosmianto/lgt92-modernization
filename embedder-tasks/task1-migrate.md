This is a legacy STM32L072 project. I want to migrate the build system from Makefile to CMake. The codebase is a bit messy so you need to figure out the correct CMake command to use.

Some things you need to know:

* Ensure the current build system is working. For this project, I only want to use GCC compiler and CMake.
* In the case of failure build process, make the necessary changes only to the relevant files.
* I don't need files from other IDEs like EWARM or MDK aren't needed.
* Clean up the unused software modules, but keep the LoRaWAN-related files. Only target STM32L072 and SX1276.
* Create a README.md which contains the instruction to build the firmware binary.
* Put the final CMakeLists.txt in the project root (as well as the build folder).