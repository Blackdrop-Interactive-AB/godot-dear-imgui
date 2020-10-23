#include "native_imgui.h"
#include "scene/resources/mesh.h"


/*
void imgui_native::_bind_methods() {
}

imgui_native::imgui_native() {
	ImGuiContext * context = ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();

	ImGui::NewFrame();
	ImGui::Text("Hello, world!");
	ImGui::EndFrame();
	ImGui::Render();
	ImDrawData *draw_data = ImGui::GetDrawData();

	if (draw_data->Valid) {
		int test = 5;
	}
}

imgui_native::~imgui_native() {
}
*/

 

void native_imgui::_bind_methods() {
	ClassDB::bind_method(D_METHOD("testrender"), &native_imgui::_process);
}

void native_imgui::_process(float delta, RID parent) {
	bool truebool = true;
	
	ImGui::NewFrame();
	ImGui::Begin("Test");
	ImGui::Text("ABOUT THIS DEMO:");
	ImGui::BulletText("Sections below are demonstrating many aspects of the library.");
	ImGui::BulletText("The \"Examples\" menu above leads to more demo contents.");
	ImGui::BulletText("The \"Tools\" menu above gives access to: About Box, Style Editor,\n"
					  "and Metrics (general purpose Dear ImGui debugging tool).");
	ImGui::Separator();

	ImGui::Text("PROGRAMMER GUIDE:");
	ImGui::BulletText("See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
	ImGui::BulletText("See comments in imgui.cpp.");
	ImGui::BulletText("See example applications in the examples/ folder.");
	ImGui::BulletText("Read the FAQ at http://www.dearimgui.org/faq/");
	ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
	ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");
	ImGui::Separator();

	ImGui::Text("USER GUIDE:");
	ImGui::End();
	ImGui::EndFrame(); 

	ImGui::Render(); 
	
	Render(delta, nullptr, get_canvas_item());
}



Vector<Array> native_imgui::extract_imgui_data() {
	ImDrawData *draw_dat = ImGui::GetDrawData();

	// validate data
	if (!draw_dat->Valid) print_error("IMGUI: DRAW DATA NOT VALID");

	
	Vector<Array> arrays;
	// How many meshes
	for (uint32_t i = 0; i < draw_dat->CmdListsCount; i++) {
		ImDrawList * list = draw_dat->CmdLists[i];

		Array temp;
		temp.resize(ArrayMesh::ARRAY_MAX);
	

		Vector<Vector2> vertices;
		Vector<Color> colors;
		Vector<Vector2> uvs;
		Vector<int> indices;

		for (uint32_t j = 0; j < list->VtxBuffer.size(); j++) {
			// vertex pos
			ImVec2 im_vert = list->VtxBuffer[j].pos;
			Vector2 godot_vert(im_vert.x, im_vert.y);

			// vertex colour
			ImU32 im_col = list->VtxBuffer[j].col;
			uint8_t R = (im_col & 0xFF) / 255;
			uint8_t G = ((im_col >> 8) & 0xFF) / 255;
			uint8_t B = ((im_col >> 16) & 0xFF) / 255;
			uint8_t A = ((im_col >> 24) & 0xFF) / 255;
			Color godot_col(R, G, B, A);
			// Vertex uv
			ImVec2 im_uv = list->VtxBuffer[j].uv;
			Vector2 godot_uv(im_uv.x, im_uv.y);

			uvs.push_back(godot_uv);
			vertices.push_back(godot_vert);
			colors.push_back(godot_col);
		}

		for (uint32_t j = 0; j < list->IdxBuffer.size(); j++) {
			indices.push_back(list->IdxBuffer[j]);
		}


		temp[(int)ArrayMesh::ArrayType::ARRAY_VERTEX] = vertices;
		temp[(int)ArrayMesh::ArrayType::ARRAY_INDEX] = indices;
		temp[(int)ArrayMesh::ArrayType::ARRAY_COLOR] = colors;
		temp[(int)ArrayMesh::ArrayType::ARRAY_TEX_UV] = uvs;

		arrays.push_back(temp);

	}

	


	return arrays;
}

void native_imgui::Render(float delta, ImDrawData *draw_data, RID parent) {

	Vector<Array> arrays = extract_imgui_data();
	for (uint32_t i = 0; i < arrays.size(); i++) {
		Vector<Color> temp = arrays[i][ArrayMesh::ARRAY_COLOR];
		mesh.add_surface_from_arrays(Mesh::PrimitiveType::PRIMITIVE_TRIANGLES, arrays[i]);


		VisualServer->canvas_item_clear(get_canvas_item());
		VisualServer->canvas_item_set_clip(get_canvas_item(), true); 

		VisualServer->canvas_item_add_mesh(get_canvas_item(), mesh.get_rid(), Transform2D(), Color(), imgtex.get_rid());

	}
}

void native_imgui::RebuildFontAtlas() {


}

native_imgui::native_imgui() {
	count = 0;
	this->VisualServer = VisualServer::get_singleton();
 

	print_line("Setting up IMGUI");

	newChild = VisualServer->canvas_item_create();

	
	context = ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	ImGui::SetCurrentContext(context);

	io.Fonts->AddFontDefault();

	

	int width, height, bytesPerPixel;
	unsigned char *pixels = NULL;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &bytesPerPixel);


	PoolByteArray test;

	for (uint32_t i = 0; i < width * height * bytesPerPixel; i++) {
		test.push_back(pixels[i]);
	}

	Image img(width, height, false, Image::Format::FORMAT_RGBA8, test); 

	imgtex.create_from_image(img.duplicate(), 0);

	io.Fonts->TexID = ImTextureID(100);

	io.Fonts->ClearTexData();


	io.DeltaTime = 1.0 / 60.0;
	io.DisplaySize.x = 	GLOBAL_GET("display/window/size/width"); // set the current display width
	io.DisplaySize.y = GLOBAL_GET("display/window/size/height");

}
