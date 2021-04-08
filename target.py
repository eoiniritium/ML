import os

activation = lambda number, length : format(number, 'b').zfill(length) # Get number, convert to binary and make it long enough. Must double everytime in order to make the 1 shift up everytime

imgDIR = str(input("DIR -> "))
a = int(input("Output dimensions -> "))

b = 1
for i in range(a):

    loc = imgDIR + "\\" + str(i) + "\\expected.txt"
    if not os.path.exists(loc):
        f = open(loc, 'x') # Create if not exist
        f.close()

    f = open(loc, 'w')

    data = list(activation(b, a))
    b = b * 2 # Shift 1 forwards

    f.write(str(data).replace("[", "").replace("]", "").replace(" ", "").replace('"', "").replace("'", "")[::-1])
    f.close()