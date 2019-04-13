from PIL import Image
import os

def create_outline(input_dir, in_name, out_name):
    # PIL accesses images in Cartesian co-ordinates, so it is Image[columns, rows]
<<<<<<< HEAD
    img = Image.open("%s/%s" % (input_dir, in_name))
=======
    img = Image.open(in_name) 
>>>>>>> master
    pixels = img.load() # create the pixel map

    new_img = Image.new('RGB', img.size, 'white')
    new_img_pixels = new_img.load()

    thresh = 50
    white = (255,255,255)

    def is_white(pixel):
        return pixel[1] == 255 and pixel[2] == 255 and pixel[3] == 255

    for i in range(3, img.size[0] - 3):    # for every col:
        for j in range(3, img.size[1] - 3):    # For every row
            #print(pixels[i,j])
            if not is_white(pixels[i,j]) and (is_white(pixels[i-1,j]) or is_white(pixels[i+1,j]) or is_white(pixels[i,j-1]) or is_white(pixels[i,j+1])):
<<<<<<< HEAD
                for l in range(i-5, i+5):
                    for m in range(j-3, j+3):
                        new_img_pixels[l,m] = (0, 0, 255)#pixels[l,m]
=======
                for l in range(i-3, i+3):
                    for m in range(j-1, j+1):
                        new_img_pixels[l,m] = (0,0,255)#pixels[l,m]
>>>>>>> master
    
    new_img.save(out_name)

def main():
<<<<<<< HEAD
    input_dir = "/home/luke/Documents/prisvg/miralens/donut_small"
    for filename in os.listdir(input_dir):
        create_outline(input_dir, filename, "/home/luke/Documents/prisvg/miralens/round1/%s" % filename)

main()
=======
    input_dir = "/home/luke/Documents/prisvg/miralens/donut_double"
    for filename in os.listdir(input_dir):
        create_outline(input_dir + "/" + filename, "/home/luke/Documents/prisvg/miralens/round2/%s" % filename)


main()
>>>>>>> master
