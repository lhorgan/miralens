import pyglet
import math
from pyglet import clock
i = 0
fps = 240


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


class SquareImage:
    def __init__(self, batch, x_pos, y_pos, image_size):
        black = pyglet.image.load("black.png")
        self.b = black.get_region(0, 0, image_size, image_size)
        white = pyglet.image.load("white.png")
        self.w = white.get_region(0, 0, image_size, image_size)
        self.sprite = pyglet.sprite.Sprite(self.b, x=x_pos, y=y_pos, batch=batch)

    def black(self):
        self.sprite.image = self.b
        return self

    def white(self):
        self.sprite.image = self.w
        return self


class Game(pyglet.window.Window):
    def __init__(self):
        clock.set_fps_limit(fps)
        self.fps_display = clock.ClockDisplay()
        monitor = Monitor(1080, 1920, 13.12, 23.43)
        image_size = monitor.mm_to_px(42)
        image_spacing = monitor.mm_to_px(3.175)
        rows = 4
        cols = 5
        window_width = (cols+1)*image_spacing+cols*image_size
        # extra row for fps display and sync sensor
        window_height = (rows+2)*image_spacing+(rows+1)*image_size
        pyglet.window.Window.__init__(self, width=window_width, height=window_height)
        self.batch_draw = pyglet.graphics.Batch()
        squares = []
        for i in range(rows+1):
            for j in range(cols):
                x = window_height - (j+1)*(image_size + image_spacing)
                y = window_width - (i+1)*(image_size+image_spacing)
                squares.append(SquareImage(self.batch_draw, x, y, image_size))
        self.squares = squares[:-4]
        self.keys_held = []
        self.schedule = pyglet.clock.schedule_interval(func=self.update, interval=1/float(fps*2))

    def on_draw(self):
        self.clear()
        self.fps_display.draw()
        self.batch_draw.draw()
        for square in self.squares:
            square.sprite.draw()

    def on_key_press(self, symbol, modifiers):
        self.keys_held.append(symbol)
        # print "The 'RIGHT' key was pressed"

    def on_key_release(self, symbol, modifiers):
        self.keys_held.pop(self.keys_held.index(symbol))
        # print "The 'RIGHT' key was released"

    def update(self, interval):
        if pyglet.window.key.RIGHT in self.keys_held:
            global i
            if i % 2 == 0:
                for square in self.squares:
                    square.black()
                i = 0
            else:
                for square in self.squares:
                    square.white()
                i = 1
            i += 1


if __name__ == "__main__":
    window = Game()
    pyglet.app.run()
