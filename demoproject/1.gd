extends native_imgui


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var button = false;
var selected = true;
var temp = 5.0
var color = Color(1.0, 0.3, 1.0)

var integer = 0

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func _process(delta):
	ImGui_Begin("Test windows", true)
	ImGui_Text("This window lives only to show you that we can have multiple windows")
	
	ImGui_End()	
 
 
