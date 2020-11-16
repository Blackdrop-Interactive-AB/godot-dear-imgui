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
	ImGui_Begin("Test1", true)
	button = ImGui_Button("Some button1", Vector2(150.0, 30.0))
	ImGui_ArrowButton("test", ImGuiDir_Left)
	if (button):
		ImGui_Text("Test1")
		
	if (ImGui_TreeNode("Basic1")):
		ImGui_BulletText("Sect1ions below are demonstrating many aspects of the library.")
		ImGui_BulletText("The 1\"Examples\" menu above leads to more demo contents.")
		ImGui_BulletText("The 1\"Tools\" menu above gives access to: About Box, Style Editor, \n and Metrics (general purpose Dear ImGui debugging tool).")
		ImGui_Separator()
		ImGui_TreePop()
	
	integer = ImGui_VSliderInt("1Label fff", Vector2(400.0, 200.0), integer, 0, 100)
	get_parent().color = ImGui_ColorEdit3("Th1e same color again", color)
	ImGui_InputText("1label", "", 0)
	  
	
	ImGui_Text("PRO1GRAMMER GUIDE:")
	ImGui_BulletText("See the S1howDemoWindow() code in imgui_demo.cpp. <- you are here!")
	ImGui_BulletText("See co1mments in imgui.cpp.")
	ImGui_BulletText("See exampl1e applications in the examples/ folder.")
	ImGui_BulletText("Read the F1AQ at http://www.dearimgui.org/faq/")
	ImGui_BulletText("Set 'io.Co1nfigFlags |= NavEnableKeyboard' for keyboard controls.")
	ImGui_BulletText("Set 'io.C1onfigFlags |= NavEnableGamepad' for gamepad controls.")
	#apa = ImGui_InputTextWithHint("Test label", "this is a hint", apa, 0)
	ImGui_Separator();
	ImGui_LabelText("This is1 a test for a test")
	ImGui_LabelTextV("This is a label1", "This is just some text loreipsum")
	temp = ImGui_InputFloat("Test 1value", temp, 0.1, 0.2, "%.3f")
	get_parent().set_position(ImGui_InputFloat2("Color but1tons position", get_parent().get_position()))
	ImGui_InputTextMultiline("La1bel", "t1est string")
	ImGui_LogText("Tes1t")
	ImGui_ListBox("Te1st label", 0, [12,45])
	ImGui_Text("USER1 GUIDE:")
	ImGui_PlotLines("Lab1el 2", [1,2,3,4,5, 6,7,8,9,10])
	ImGui_ProgressBar(0.4, get_parent().get_position())
	selected = ImGui_MenuItem("Ma1in menu bar", "", selected, true);
	color = ImGui_ColorPicker3("Pi1ck some", color)
	
	ImGui_End()
	ImGui_EndFrame(); 
	ImGui_Render();  

	
	
	


