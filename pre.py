import os
from PIL import Image

def pixelvalues(a, x): # Images DIR, Num of images
    b = a + "pixelvalues\\"

    if not os.path.exists(b):
        os.makedirs(b)

    for i in range(0, x + 1):
        img = Image.open(a + str(i) + ".png").convert('L')
        img.save(a + str(i) + ".png")

    for i in range(0, x + 1):
        im = Image.open(a + str(i) + ".png")
        height, width = im.size
        data = []

        for ecs in range(im.width):
            for why in range(im.height):
                data.append(str(im.getpixel((ecs, why))))
        
        try:
            f = open(b + str(i) + ".txt", 'x')
            f.close()
        except:
            pass

    f = open(b + str(i) + ".txt", 'w')
    f.write(",".join(data))
    f.close()

def scaler(sizex, sizey, location, number):

    size = (sizex, sizey)

    for i in range(0, number + 1):
        image = Image.open(location + "\\" + str(i) + ".png")
        image = image.resize(size, Image.BILINEAR)
        image = image.save(location + "\\" + str(i) + ".png")
