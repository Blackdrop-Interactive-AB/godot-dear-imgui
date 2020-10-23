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
	ImDrawData *draw_data = ImGui::GetDrawData();

	Render(delta, draw_data, get_canvas_item());
}

void native_imgui::Render(float delta, ImDrawData *draw_data, RID parent) {



	Vector<Vector2> vertices;
	Vector<Color> colors;
	Vector<Vector2> uvs;
	Vector<int> indices;

	int factor = 100;

	// First face
	vertices.push_back(Vector2(0, 0) * factor);
	vertices.push_back(Vector2(1, 0) * factor);
	vertices.push_back(Vector2(1, 1) * factor);

	// Second face	
	vertices.push_back(Vector2(1, 1) * factor);
	vertices.push_back(Vector2(0, 1) * factor);
	vertices.push_back(Vector2(0, 0) * factor);

	

	for (uint32_t i = 0; i < vertices.size(); i++)
		indices.push_back(i);
	
	VisualServer->canvas_item_set_parent(newChild, parent);
	VisualServer->canvas_item_set_draw_index(newChild, 0);



	arrays.resize(ArrayMesh::ARRAY_MAX);
	arrays[(int)ArrayMesh::ArrayType::ARRAY_VERTEX] = vertices;
	arrays[(int)ArrayMesh::ArrayType::ARRAY_INDEX] = indices;
	 
	mesh.add_surface_from_arrays(Mesh::PrimitiveType::PRIMITIVE_TRIANGLES, arrays);
	 
;

	//VisualServer->canvas_item_clear(newChild);
	VisualServer->canvas_item_set_clip(newChild, true); 

	VisualServer->canvas_item_add_mesh(newChild, mesh.get_rid(), Transform2D(), Color(1.0, 1.0, 1.0, 1.0));

	update();

	/*
	// Let's process the data
	uint32_t neededNodes = 0;
	for (uint32_t i = 0; i < draw_data->CmdListsCount; i++) {
		neededNodes += draw_data->CmdLists[i]->CmdBuffer.Size;
	}
 
	while (children.size() < neededNodes) {
		RID newChild = VisualServer->canvas_item_create();
		VisualServer->canvas_item_set_parent(newChild, parent);
		VisualServer->canvas_item_set_draw_index(newChild, children.size());
		
		children.push_back(newChild);
		meshes.push_front(new ArrayMesh());
	}

	draw_data->ScaleClipRects(ImGui::GetIO().DisplayFramebufferScale);
 

	for (uint32_t n = 0, nodeN = 0; n < draw_data->CmdListsCount; n++, nodeN++) {
		ImDrawList *cmdList = draw_data->CmdLists[n];
		int idxOffset = 0;

		int nVert = cmdList->VtxBuffer.Size;

		Vector<Vector2> vertices; 
		Vector<Color> colors;
		Vector<Vector2> uvs;

		// Build the vertexes from ImGui
		for (int i = 0; i < cmdList->VtxBuffer.Size; i++) {
			auto v = cmdList->VtxBuffer[i];
			vertices.push_back(Vector2(v.pos.x, v.pos.y));
			// need to reverse the color bytes
			unsigned int c0 = 255;
			(v.col & 0xFF);
			unsigned int c1 = 255;
			((v.col >> 8) & 0xFF);
			unsigned int c2 = 255;
			((v.col >> 16) & 0xFF);
			unsigned int c3 = 255;
			((v.col >> 24) & 0xFF);
			colors.push_back(Color(c0, c1, c2, c3));

			print_line(vformat("x %d. y %d w %d", v.uv.x, v.uv.y, c3));
			uvs.push_back(Vector2(1, v.uv.y));
		}
	
		for (int cmdi = 0; cmdi < cmdList->CmdBuffer.Size; cmdi++) {
			ImDrawCmd drawCmd = cmdList->CmdBuffer[cmdi];

			Vector<int> indices;

			for (int i = idxOffset, j = 0; i < idxOffset + drawCmd.ElemCount; i++, j++) {
				indices.push_back(cmdList->IdxBuffer[i]);
			}

			auto arrays = Array();

			arrays.resize(ArrayMesh::ARRAY_MAX);
			arrays[(int)ArrayMesh::ArrayType::ARRAY_VERTEX] = vertices;
			arrays[(int)ArrayMesh::ArrayType::ARRAY_COLOR] = colors;
			arrays[(int)ArrayMesh::ArrayType::ARRAY_TEX_UV] = uvs;
			arrays[(int)ArrayMesh::ArrayType::ARRAY_INDEX] = indices;
	

			
			ArrayMesh mesh = *meshes[nodeN];
			mesh.clear_surfaces();
		
			mesh.add_surface_from_arrays(Mesh::PrimitiveType::PRIMITIVE_TRIANGLES, arrays);
			
			RID child = children[nodeN];
			  
			VisualServer->canvas_item_clear(child);
			VisualServer->canvas_item_set_clip(child, true);
			VisualServer->canvas_item_set_custom_rect(child, true, Rect2(drawCmd.ClipRect.x, drawCmd.ClipRect.y, drawCmd.ClipRect.z - drawCmd.ClipRect.x, drawCmd.ClipRect.w - drawCmd.ClipRect.y));
			
			VisualServer->canvas_item_add_mesh(child, mesh.get_rid(), get_transform(), Color(1.0, 1.0, 1.0), VisualServer->get_test_texture());
	
		}
	}
	*/
}

void native_imgui::RebuildFontAtlas() {
	/*
	ImGuiIO &io = ImGui::GetIO();
	int width, height, bytesPerPixel;
	uint8_t * pixels = nullptr;
	//PackedByteArray p_data;


	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &bytesPerPixel);
	p_data.resize(width * height * bytesPerPixel);


	for (uint32_t i = 0; i < width * height * bytesPerPixel; i++) {
		p_data.set(i, pixels[i]);
	}

	Image img = Image(width, height, false, Image::Format::FORMAT_RGBA8, p_data);

 

	
	imgtex.create_from_image(img.duplicate());
	
	io.Fonts->SetTexID(ImTextureID(100));
	io.Fonts->ClearTexData();
	*/

}

native_imgui::native_imgui() {
	count = 0;
	this->VisualServer = VisualServer::get_singleton();
 

	print_line("Setting up IMGUI");	
	context = ImGui::CreateContext();
	ImGui::SetCurrentContext(context);

	ImGuiIO &io = ImGui::GetIO();
	io.Fonts->AddFontDefault();

	
	newChild = VisualServer->canvas_item_create();

	int width, height;
	unsigned char *pixels = NULL;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

	io.DeltaTime = 1.0 / 60.0;
	 get_process_delta_time();
	io.DisplaySize.x = 	GLOBAL_GET("display/window/size/width"); // set the current display width
	io.DisplaySize.y = GLOBAL_GET("display/window/size/height");

	RebuildFontAtlas();

}
