import pyglet
import math
from pyglet import clock
i = 0
fps = 240
black = pyglet.image.load("black.png")
white = pyglet.image.load("white.png")

import sys
import os
from PIL import Image
import random


# luke's code
def make_grid_helper(rows, cols, box_width, box_height, spacing, filenames, image_name):
    total_width = (box_width * cols) + ((cols - 1) * spacing)
    # extra row for dv sync
    total_height = (box_height * (rows+1)) + (rows * spacing)
    canvas = Image.new('RGB', (total_width, total_height))

    x_offset = 0
    y_offset = 0
    images_placed_in_row = 0
    for filename in filenames:
        # print("pasting %s" % filename)
        img = Image.open(filename)
        img = img.resize((box_width, box_height), Image.ANTIALIAS)
        tup = (x_offset, y_offset)
        # print(tup)
        canvas.paste(img, tup)
        images_placed_in_row += 1

        x_offset += box_width + spacing
        if images_placed_in_row == cols:
            images_placed_in_row = 0
            y_offset += (box_height + spacing)
            x_offset = 0

    # add white box for dv sync
    img = Image.open("white.png")
    img = img.resize((box_width, box_height), Image.ANTIALIAS)
    tup = (4*(box_width+spacing), 4*(box_height+spacing))
    canvas.paste(img, tup)
    canvas.save("%s.png" % image_name)


def parse_directory(rows, cols, directory):
    image_lists = [[]]

    for filename in os.listdir(directory):
        image_lists[-1].append(directory + "\\" + filename)
        if len(image_lists[-1]) == rows * cols:
            image_lists.append([])

    image_lists = image_lists[:-1]

    return image_lists


def make_grid(rows, cols, box_width, box_height, spacing, directory):
    image_lists = parse_directory(rows, cols, directory)
    output_dir = "C://Users//miralens//Documents//miralens//frames3"
    if(not os.path.exists(output_dir)):
        os.mkdir(output_dir)

    for i in range(len(image_lists)):
        make_grid_helper(rows, cols, box_width, box_height, spacing, image_lists[i], "%s\\frame_%02d" % (output_dir, i))
        # print("\n")

# josh's code
class Monitor:
    def __init__(self, height_px, width_px, height_in, width_in):
        self.height_px = height_px
        self.width_px = width_px
        self.height_in = height_in
        self.width_in = width_in
        self.height_mm = self.height_in * 25.4
        self.width_mm = self.width_in * 25.4

    def mm_to_px(self, square_size):
        px_per_mm = self.height_px/self.height_mm
        return int(math.floor(square_size*px_per_mm))


monitor = Monitor(1080, 1920, 13.12, 23.43)
image_size = monitor.mm_to_px(42)
image_spacing = monitor.mm_to_px(3.175)
rows = 4
cols = 5
window_width = (cols+1)*image_spacing+cols*image_size
# extra row for fps display and sync sensor
window_height = (rows+3)*image_spacing+(rows+2)*image_size
make_grid(rows, cols, image_size, image_size, image_spacing, "C://Users//miralens//Documents//miralens//round2")
frames_dir = "C://Users//miralens//Documents//miralens//frames3"
imgs = []
for file in os.listdir(frames_dir):
    imgs.append(pyglet.image.load(frames_dir+"\\"+file))

class SquareImage:
    def __init__(self, batch, x_pos, y_pos, image_size):
        self.b = black
        self.w = imgs
        self.count = 0
        self.sprite = pyglet.sprite.Sprite(self.b, x=x_pos, y=y_pos, batch=batch)

    def black(self):
        self.sprite.image = self.b
        return self

    def white(self):
        self.sprite.image = self.w[self.count]
        self.count = (self.count + 1) % len(imgs)
        return self


class Game(pyglet.window.Window):
    def __init__(self):
        clock.set_fps_limit(fps)
        self.fps_display = clock.ClockDisplay()
        pyglet.window.Window.__init__(self, width=window_width, height=window_height)
        self.batch_draw = pyglet.graphics.Batch()
        x = image_spacing
        y = window_height - 5*(image_size+image_spacing)
        self.square = SquareImage(self.batch_draw, x, y, image_size)
        self.run = False
        self.schedule = pyglet.clock.schedule_interval(func=self.update, interval=1/float(fps*2))

    def on_draw(self):
        self.clear()
        self.fps_display.draw()
        self.batch_draw.draw()
        self.square.sprite.draw()

    def on_key_press(self, symbol, modifiers):
        if symbol == pyglet.window.key.SPACE:
            self.run = not self.run

    def update(self, interval):
        if self.run:
            global i
            if i % 2 == 0:
                self.square.black()
                i = 0
            else:
                self.square.white()
                i = 1
            i += 1


if __name__ == "__main__":
    window = Game()
    pyglet.app.run()
