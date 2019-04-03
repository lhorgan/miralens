import pyglet
from pyglet import clock
i = 0
fps_display = clock.ClockDisplay()

class ImageSprite(pyglet.sprite.Sprite):
    def __init__(self, batch, img):
        pyglet.sprite.Sprite.__init__(self, img, x = 300, y = 300)
        self.b = pyglet.image.load("black.png")
        self.w = pyglet.image.load("white.png")
	
    def black(self):
        self.image = self.b
        return self

    def white(self):
        self.image = self.w    
        return self

class Game(pyglet.window.Window):
    def __init__(self):
        pyglet.window.Window.__init__(self, width = 600, height = 600)
	fps_display = clock.ClockDisplay()
        self.batch_draw = pyglet.graphics.Batch()
        self.player = ImageSprite(batch = self.batch_draw, img = pyglet.image.load("white.png"))
        self.keys_held = []      
        self.schedule = pyglet.clock.schedule_interval(func = self.update, interval = 1/60.) 

    def on_draw(self): 
        self.clear()      
	fps_display.draw()   
        self.batch_draw.draw()
        self.player.draw()  

    def on_key_press(self, symbol, modifiers):
        self.keys_held.append(symbol)
#            print "The 'RIGHT' key was pressed"

    def on_key_release(self, symbol, modifiers):
        self.keys_held.pop(self.keys_held.index(symbol))
 #       print "The 'RIGHT' key was released"

    def update(self, interval):
        if pyglet.window.key.RIGHT in self.keys_held:
		global i
		if i%2 == 0:
			self.player = self.player.black()
		else:
			self.player = self.player.white()
		i=i+1
if __name__ == "__main__":
    window = Game()
    pyglet.app.run()
