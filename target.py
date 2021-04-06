import os

print("Target generator: ")


tPath = str(input("Folder dir -> "))

if not os.path.exists(tPath):
    os.mkdir(tPath)

num = int(input("No. of different classifications -> "))
dim = int(input("Output dimension -> "))