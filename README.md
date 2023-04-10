# pico-dev - WIP 
Development setup for RP2040 containing FreeRTOS, TinyUSB and UnitTesting(Catch2 + FakeIt + gcov/lcov) mostly in docker container  

# Folder structure  
- `source/` - source files for application with `main.cpp`  
- `test/` - test file for testing of application source files  
- `library/` - libraries like FreeRTOS, Tiny usb and others  
- `build/` - build folder for MCu binaries and unit tests binaries  
  
# Docker  
Compilation is done in docker container  
This container have no persistent data, after command is stopped  
Project folder is mapped into docker folder `/project/`  

Main components of Docker container are  
- lcov  
- picotool  
- pico-sdk  
- openocd (currently not used)  

# Compiling  
There are two main environments for compiling due their difference are separated.  
- Binary - for RP2040 binary compilarion  
- Test - for Unit test compilation  

Both have separated CMake file in folder `source/` and `test/` mainly due to sdk-init script of pico-sdk. Which setup environment in which is complicated to compile unit tests. But both CMake files are merged into one by using ExternalProject module of CMake.  

# Unit testing  
Test files are linked to source files by prefix `"test_" + source_file_name + ".cpp"`  
Unit test are build and must be run in docker due to different interpret which could not be compatible with host.  
Makefile target `run_test` will execute unit tests in container and print output  

# VSCode Integration  
Debugging is integrated into vscode but is done localy on host machine  
Building is not integrated is run by Makefile targets  
Unit test are not integrated but probably could be by usage of C++ [Test Mate](https://github.com/matepek/vscode-catch2-test-adapter)  
  - There is problem with running test in docker because test binary cannot be execute on host  
  - Using "wrapper" is not working, stuck on `discovering tests`  
  - Source files will have to be mapped to host machine similar to GDB  
  - Configuration of extension  
```json  
"testMate.cpp.test.advancedExecutables": [  
        {  
            "pattern": "build/test/utest",  
            "executionWrapper": {  
                "path": "/bin/sh",  
                "args": [ "-c", "${workspaceFolder}/run_test.sh \"${cmd}\" ${argsStr} 2>&1" ]  
            },  
            "sourceFileMap": {  
                "/project": "${workspaceFolder}"  
            }  
        }  
    ],  
```  

# Debugging  
Is done via VSCode cortex-debug extension can can be done by any other mean.  
Content of launch.json for cortex debug configuration  
Debugging is done outside of container due to unresolved issues with connection to cortex-debug.  
Because during compilation symbols are referenced to file position in container path substitution is required on order to properly step through files in VSCode. If stepping through pico-sdk files os required, pico-sdk must be cloned to local device updated absolute path to substitute (second line of `preLaunchCommands`).  

```json  
{  
  "version": "0.2.0",  
  "configurations": [  
    {  
      "name": "OCD - Pico Debug",  
      "cwd": "${workspaceRoot}",  
      "executable": "${workspaceRoot}/build/sample.elf",  
      "request": "launch",  
      "type": "cortex-debug",  
      "servertype": "openocd",  
      "gdbPath" : "gdb-multiarch",  
      "device": "RP2040",  
      "configFiles": [  
          "interface/cmsis-dap.cfg",  
          "target/rp2040.cfg"  
      ],  
      "svdFile": "${workspaceRoot}/rp2040.svd",  
      "runToEntryPoint": "main",  
      "postRestartCommands": [  
          "break main",  
          "continue"  
      ],  
      "preLaunchCommands": [  
        "set substitute-path /project ${workspaceRoot}",  
        "set substitute-path /usr/share/pico_sdk /home/petr/development/pico-sdk",  
      ],  
    }  
  ]  
}  
```  

# Makefile  
Main targets:  
`docker-build` - build container requiren for most of other targets  
`binary` - Compile binary for RP2040  
`flash` - Flash binary into RP2040 connected via SWD (RPi Debug Probe)  
`picotool`-flash - Use picotool to flash binary into device via USB connection  
`tests` - Compile unit tests  
`run_test` - Run unit tests  
`coverage` - Create coverage report for unit tests  
`report_coverage` - Create HTML coverage report by lcov  
`clean` - Remove build folder  

There are another targets are these are currently used for debugging or testing of system  

# TODO
- [ ] - Debugging thought container, openocd in container, cortex-debug attached into debug serve
- [ ] - Test integration into VSCode
- [ ] - Coverage report integration into VSCode (line coverage + report viewer)
- [ ] - Change location of coverage report output folder
- [ ] - Better FreeRTOS support
- [ ] - TinyUSB support
- [ ] - External custom library support
