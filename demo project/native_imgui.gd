extends native_imgui

var button = false;
var selected = true;
var temp = 5.0
var color = Color(1.0, 0.3, 1.0)

var integer = 0
# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.
 
func _input(event):
	input(event)
 
func _process(delta):	
	ImGui_NewFrame();

	ImGui_Begin("Test", true)
	button = ImGui_Button("Some button", Vector2(150.0, 30.0))
	ImGui_ArrowButton("test", ImGuiDir_Left)
	if (button):
		ImGui_Text("Test")
		
	if (ImGui_TreeNode("Basic")):
		ImGui_BulletText("Sections below are demonstrating many aspects of the library.")
		ImGui_BulletText("The \"Examples\" menu above leads to more demo contents.")
		ImGui_BulletText("The \"Tools\" menu above gives access to: About Box, Style Editor, \n and Metrics (general purpose Dear ImGui debugging tool).")
		ImGui_Separator()
		ImGui_TreePop()
	
	integer = ImGui_VSliderInt("Label fff", Vector2(400.0, 200.0), integer, 0, 100)
	get_parent().color = ImGui_ColorEdit3("The same color again", color)
	ImGui_InputText("label", "", 0)
	  
	
	ImGui_Text("PROGRAMMER GUIDE:")
	ImGui_BulletText("See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!")
	ImGui_BulletText("See comments in imgui.cpp.")
	ImGui_BulletText("See example applications in the examples/ folder.")
	ImGui_BulletText("Read the FAQ at http://www.dearimgui.org/faq/")
	ImGui_BulletText("Set 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.")
	ImGui_BulletText("Set 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.")
	#apa = ImGui_InputTextWithHint("Test label", "this is a hint", apa, 0)
	ImGui_Separator();
	ImGui_LabelText("This is a test for a test")
	ImGui_LabelTextV("This is a label", "This is just some text loreipsum")
	temp = ImGui_InputFloat("Test value", temp, 0.1, 0.2, "%.3f")
	get_parent().set_position(ImGui_InputFloat2("Color buttons position", get_parent().get_position()))
	ImGui_InputTextMultiline("Label", "test string")
	ImGui_LogText("Test")
	ImGui_ListBox("Test label", 0, [12,45])
	ImGui_Text("USER GUIDE:")
	ImGui_PlotLines("Label 2", [1,2,3,4,5, 6,7,8,9,10])
	ImGui_ProgressBar(0.4, get_parent().get_position())
	selected = ImGui_MenuItem("Main menu bar", "", selected, true);
	color = ImGui_ColorPicker3("Pick some", color)
	
	ImGui_End()
	ImGui_EndFrame(); 
	ImGui_Render();  

	
	
	


