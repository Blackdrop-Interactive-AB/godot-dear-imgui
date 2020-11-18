extends native_imgui


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var button = false;
var selected = true;
var temp = 5.0
var color = Color(1.0, 0.3, 1.0)
var multilineInput = ""
var integer = 0

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func _process(delta):
	ImGui_Begin("Testing window that effects parent", true)
	button = ImGui_Button("A simple button", Vector2(150.0, 30.0))
	ImGui_ArrowButton("Directional button that test our enums", ImGuiDir_Left)
	if (button):
		ImGui_Text("You clicked the button")	
	
	ImGui_Text("Lorem ipsum dolor sit amet, consectetur adipiscing elit.:")
	ImGui_BulletText("Donec a gravida tortor.")
	ImGui_BulletText("Aliquam ut suscipit orci.")
	ImGui_BulletText("See exampl1e applications in the examples/ folder.")
	ImGui_BulletText("Maecenas tristique est magna, et ultricies dolor tempus a. Phasellus tincidunt velit massa")
	ImGui_BulletText("Nam at metus quis augue pretium vehicula ullamcorper id ante.")
	ImGui_BulletText("Vestibulum in est magna. Duis semper libero nunc.")
	
	if (ImGui_TreeNode("This a tree node")):
		ImGui_BulletText("This is a new node that you expanded.")
		ImGui_BulletText("It just works..")
		ImGui_BulletText("Let's test a separator.")
		ImGui_Separator()
		ImGui_TreePop()
		
	ImGui_Separator()
	ImGui_LabelText("This is is a label")
	ImGui_LabelTextV("This is a labael which is variadic", "This is just some text loreipsum")
	
	temp = ImGui_InputFloat("This is input float test", temp, 0.1, 0.2, "%.3f")
	get_parent().set_position(ImGui_InputFloat2("This sets the position of the parent", get_parent().get_position()))
	multilineInput = ImGui_InputTextMultiline("Multi line string input, give it a shot. Limited to 64 chars atm", multilineInput)
 
	ImGui_ListBox("List box with some values", 0, [12,45])
	ImGui_Text("Lets plot som data:")
	ImGui_PlotLines("Lab1el 2", [1,2,3,4,5, 6,7,8,9,10])
	ImGui_Text("Progression bar!:")
	ImGui_ProgressBar(0.4, Vector2(20.4, 20.5))
	selected = ImGui_MenuItem("Menu items test", "", selected, true);
	color = ImGui_ColorPicker3("Set a color for the parent, which also is color picker.", color)
	get_parent().color = color
	ImGui_End()	
		
func _input(event):
	input(event)
 
