extends ColorPicker


# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func _process(delta):
	print("tesssst") 
	
func _draw():
	draw_rect(Rect2(656,329, 870, 427), Color(1.0, 0.0,0.0, 1.0))
	print("Test")
 
