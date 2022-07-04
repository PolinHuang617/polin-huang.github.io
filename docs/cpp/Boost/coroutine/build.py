#!/usr/bin/python3
import os
import sys
import shutil

project = "boostCorotine"
buildPath = "./build/"

if sys.argv[1] in ["make", "m"]: 
    if not os.path.exists(buildPath):
        os.mkdir(buildPath, 0o755)
    os.chdir(buildPath)
    option = input("run or debug[r/d]: ")
    if option == "r":
        os.system("g++ -o %s ./main_push_pull.cpp -lboost_context -g" % (project))
        os.system("./" + project)
    elif option == "d":
        os.system("g++ -o %s ./main_push_pull.cpp -lboost_context -g" % (project))
        os.system("gdb ./" + project)
elif sys.argv[1] in ["clean", "c"]:
    shutil.rmtree(buildPath, ignore_errors=True)
    print("Deleted " + buildPath)
else:
    print("Command not found: " + sys.argv[1])
