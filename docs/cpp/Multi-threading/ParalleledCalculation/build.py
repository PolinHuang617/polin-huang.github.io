#!/usr/bin/python3
import os
import sys
import shutil

project = "parallelCalc"
buildPath = "./build/"

if sys.argv[1] in ["make", "m"]: 
    if not os.path.exists(buildPath):
        os.mkdir(buildPath, 0o755)
    os.chdir(buildPath)
    print("CMake start...")
    if not os.system("cmake .."):
        if not os.system("make"):
            print("make succeed.")
            option = input("run or debug[r/d]: ")
            if option == "r":
                os.system("./" + project)
            elif option == "d":
                os.system("gdb ./" + project)
        else:
            print("make failed")
    else:
        print("cmake failed")
elif sys.argv[1] in ["clean", "c"]:
    shutil.rmtree(buildPath, ignore_errors=True)
    print("Deleted " + buildPath)
else:
    print("Command not found: " + sys.argv[1])
