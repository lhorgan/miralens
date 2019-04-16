from PIL import Image
import os

def create_outline(input_dir, in_name, out_name):
    # PIL accesses images in Cartesian co-ordinates, so it is Image[columns, rows]
    img = Image.open("%s/%s" % (input_dir, in_name))
    pixels = img.load() # create the pixel map

    new_img = Image.new('RGB', img.size, 'blue')
    new_img_pixels = new_img.load()

    #thresh = 50
    white = (255,255,255)

    def is_white(pixel):
        return pixel[1] == 255 and pixel[2] == 255 and pixel[3] == 255

    for i in range(3, img.size[0] - 3):    # for every col:
        for j in range(3, img.size[1] - 3):    # For every row
            #print(pixels[i,j])
            if not is_white(pixels[i,j]) and (is_white(pixels[i-1,j]) or is_white(pixels[i+1,j]) or is_white(pixels[i,j-1]) or is_white(pixels[i,j+1])):
                for l in range(i-1, i+1):
                    for m in range(j-1, j+1):
                        new_img_pixels[l,m] = (255, 255, 255)#pixels[l,m]
    
    ratio = 1
    img_small = new_img.resize((int(img.size[0] * ratio), int(img.size[1] * ratio)), resample=0)
    canvas = Image.new('RGB', img.size, 'white')
    canvas.paste(img_small, ((img.size[0] - img_small.size[0]) / 2, (img.size[1] - img_small.size[1]) / 2))

    canvas.save(out_name)

def main():
    input_dir = "/home/luke/Documents/miralens2/miralens/ffslices/"
    output_dir = "/home/luke/Documents/miralens2/miralens/ffslices_frames/"
    for filename in os.listdir(input_dir):
        create_outline(input_dir, filename, "%s%s" % (output_dir, filename))

main()
