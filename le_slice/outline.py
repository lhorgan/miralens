from PIL import Image

def create_outline(in_name, out_name):
    # PIL accesses images in Cartesian co-ordinates, so it is Image[columns, rows]
    img = Image.open("/home/luke/Documents/prisvg/miralens/tourus_slices/0001.png") 
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
                for l in range(i-3, i+3):
                    for m in range(j-3, j+3):
                        new_img_pixels[l,m] = pixels[l,m]
    
    new_img.save(out_name, out_name)

def main():
    input_dir = "~/Documents/prisvg/miralens/donut_small"
    for filename in asdfk:
        create_outline(filename, "~/Documents/prisvg/round1/%s" % filename)