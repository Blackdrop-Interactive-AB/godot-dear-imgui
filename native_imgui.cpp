#include "native_imgui.h"
#include "scene/resources/mesh.h"
#include "../../core/os/os.h"


bool native_imgui::handleButtonDic(String label, bool newState) {
	bool oldState;

	if (buttonDict.has(label)) {
		oldState = buttonDict[label];

		if (oldState != newState) {
			if (newState) {
				buttonDict[label] = newState;
			}
		} else if (oldState == newState && oldState == true) {
			buttonDict[label] = !newState;
		}
	}

	return buttonDict[label];
}

inline const char *native_imgui::convertStringToChar(String string) {
	return string.utf8().get_data();
}

inline ImVec2 native_imgui::ImVec2ToVector2(const Vector2& vec) {
	return ImVec2(vec.x, vec.y);
}

void native_imgui::_bind_methods() { 
	ClassDB::bind_method(D_METHOD("ImGui_Begin", "name", "open"), &native_imgui::Begin);
	ClassDB::bind_method(D_METHOD("ImGui_BeginChild", "ImGuiID", "size", "border"), &native_imgui::BeginChild);
	ClassDB::bind_method(D_METHOD("ImGui_BeginChildFrame", "ImGuiID", "size"), &native_imgui::BeginChildFrame);
	ClassDB::bind_method(D_METHOD("ImGui_EndChildFrame"), &native_imgui::EndChildFrame);
	ClassDB::bind_method(D_METHOD("ImGui_EndChild"), &native_imgui::EndChild);
	ClassDB::bind_method(D_METHOD("ImGui_BeginCombo", "label", "preview"), &native_imgui::BeginCombo);
	ClassDB::bind_method(D_METHOD("ImGui_EndCombo"), &native_imgui::EndCombo);
	ClassDB::bind_method(D_METHOD("ImGui_BeginPopup", "str_id"), &native_imgui::BeginPopup);
	ClassDB::bind_method(D_METHOD("ImGui_EndPopup"), &native_imgui::EndPopup);
	ClassDB::bind_method(D_METHOD("ImGui_ArrowButton"), &native_imgui::ArrowButton);
	ClassDB::bind_method(D_METHOD("ImGui_Button", "text", "size"), &native_imgui::Button);
	ClassDB::bind_method(D_METHOD("ImGui_BeginGroup"), &native_imgui::BeginGroup);
	ClassDB::bind_method(D_METHOD("ImGui_EndGroup"), &native_imgui::EndGroup);
	ClassDB::bind_method(D_METHOD("ImGui_BeginPopupContextItem", "str_id"), &native_imgui::BeginPopupContextItem);
	ClassDB::bind_method(D_METHOD("ImGui_BeginPopupContextVoid", "str_id"), &native_imgui::BeginPopupContexVoid);
	ClassDB::bind_method(D_METHOD("ImGui_BeginPopupContextWindow", "str_id"), &native_imgui::BeginPopupContextWindow);
	ClassDB::bind_method(D_METHOD("ImGui_BeginPopupModal", "lable", "open"), &native_imgui::BeginPopupModal);
	ClassDB::bind_method(D_METHOD("ImGui_BeginTabBar", "str_id"), &native_imgui::BeginTabBar);
	ClassDB::bind_method(D_METHOD("ImGui_EndTabBar"), &native_imgui::EndTabBar);
	ClassDB::bind_method(D_METHOD("BeginTabBarItem"), &native_imgui::BeginTabBarItem);
	ClassDB::bind_method(D_METHOD("BeginTooltip"), &native_imgui::BeginTooltip);
	ClassDB::bind_method(D_METHOD("ImGui_Bullet"), &native_imgui::Bullet);
 

	ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "ImGui_BulletTextV", &native_imgui::BulletTextV, MethodInfo("BulletTextV"));
	ClassDB::bind_method(D_METHOD("ImGui_CalcListClipping"), &native_imgui::CalcListClipping);

	ClassDB::bind_method(D_METHOD("EndTabBarItem"), &native_imgui::EndTabBarItem);
	ClassDB::bind_method(D_METHOD("ImGui_CheckBox", "label", "value"), &native_imgui::CheckBox);
	ClassDB::bind_method(D_METHOD("ImGui_CloseCurrentPopup"), &native_imgui::CloseCurrentPopup);
	ClassDB::bind_method(D_METHOD("ImGui_ColorButton", "desc_id", "color"), &native_imgui::ColorButton);
	ClassDB::bind_method(D_METHOD("ImGui_CalcItemWidth"), &native_imgui::CalcItemWidth);
	ClassDB::bind_method(D_METHOD("ImGui_Text", "text"), &native_imgui::Text);
	ClassDB::bind_method(D_METHOD("ImGui_BulletText", "text"), &native_imgui::BulletText);
	ClassDB::bind_method(D_METHOD("ImGui_End"), &native_imgui::End);
	ClassDB::bind_method(D_METHOD("ImGui_Separator"), &native_imgui::Separator);
	ClassDB::bind_method(D_METHOD("ImGui_Render"), &native_imgui::Render);
	ClassDB::bind_method(D_METHOD("ImGui_EndFrame"), &native_imgui::EndFrame);
	ClassDB::bind_method(D_METHOD("ImGui_NewFrame"), &native_imgui::NewFrame);
	ClassDB::bind_method(D_METHOD("ImGui_BeginMenu"), &native_imgui::BeginMenu);
	ClassDB::bind_method(D_METHOD("ImGui_BeginMainMenuBar"), &native_imgui::BeginMainMenuBar);
	ClassDB::bind_method(D_METHOD("ImGui_MenuItem", "label", "shortcut", "selected", "enabled"), &native_imgui::MenuItem);
	ClassDB::bind_method(D_METHOD("ImGui_EndMenu"), &native_imgui::EndMenu);
	ClassDB::bind_method(D_METHOD("ImGui_EndMainMenuBar"), &native_imgui::EndMainMenuBar);
	ClassDB::bind_method(D_METHOD("ImGui_InputFloat", "label", "value", "step", "fastStep", "format"), &native_imgui::InputFloat);
	ClassDB::bind_method(D_METHOD("ImGui_SameLine"), &native_imgui::SameLine);
	ClassDB::bind_method(D_METHOD("ImGui_ColorPicker3", "label", "Vector3"), &native_imgui::ColorPicker3);
	ClassDB::bind_method(D_METHOD("ImGui_ColorEdit3", "label", "Vector3"), &native_imgui::ColorEdit3);
 
}

void native_imgui::process_imgui() {
	ImGuiIO &io = ImGui::GetIO();

	Vector2 godot_mouse_pos = OS::get_singleton()->get_mouse_position();
	ImVec2 mousePos(godot_mouse_pos.x, godot_mouse_pos.y);

	io.MousePos = mousePos;
	io.MouseDown[0] = OS::get_singleton()->get_mouse_button_state() == 1 ? true : false;
	io.MouseDown[1] = OS::get_singleton()->get_mouse_button_state() == 2 ? true : false;

	// This says 0, I say doubt(X)
	io.DeltaTime = 1.0 / 120.0;
	get_process_delta_time();
	 
	draw();
}
 

Vector<Array> native_imgui::extract_imgui_data() {
	ImDrawData *draw_dat = ImGui::GetDrawData();
 
	draw_dat->ScaleClipRects(ImGui::GetIO().DisplayFramebufferScale);
	
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

		for (uint32_t j = 0; j < list->CmdBuffer.Size; j++) {
			// This is just temp fix, we need to smash this into a container along with the Array, probably a dict is needed
			ImDrawCmd drawCmd = list->CmdBuffer[j];
			VisualServer->canvas_item_set_custom_rect(get_canvas_item(), true, Rect2(drawCmd.ClipRect.x, drawCmd.ClipRect.y, drawCmd.ClipRect.z - drawCmd.ClipRect.x, drawCmd.ClipRect.w - drawCmd.ClipRect.y));
		}

		// Extract information regarding verticies
		for (uint32_t j = 0; j < list->VtxBuffer.size(); j++) {
			// vertex pos
			ImVec2 im_vert = list->VtxBuffer[j].pos;
			Vector2 godot_vert(im_vert.x, im_vert.y);

			// vertex colour
			ImU32 im_col = list->VtxBuffer[j].col;
			float R = (im_col & 0xFF) / 255.0; // Bit shift magic, ImGui thinks colours are 32bit integers 0-255, Godot think they are 8 bit floats 0-1
			float G = ((im_col >> 8) & 0xFF) / 255.0;
			float B = ((im_col >> 16) & 0xFF) / 255.0;
			float A = ((im_col >> 24) & 0xFF) / 255.0;
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

void native_imgui::draw() {
	// Ugly temp fix, otherwise previous meshes will live on into next frame
	while (mesh.get_surface_count() > 0) {
		mesh.surface_remove(0);
	}
	 
	Vector<Array> arrays = extract_imgui_data();
	for (uint32_t i = 0; i < arrays.size(); i++) {
		Vector<Color> temp = arrays[i][ArrayMesh::ARRAY_COLOR];
		mesh.add_surface_from_arrays(Mesh::PrimitiveType::PRIMITIVE_TRIANGLES, arrays[i]);

		// This does not clear the backbuffer
		VisualServer->canvas_item_clear(get_canvas_item());
	  
		VisualServer->canvas_item_set_clip(get_canvas_item(), true); 

		// This adds the canvas to the rendering queue.
		VisualServer->canvas_item_add_mesh(get_canvas_item(), mesh.get_rid(), Transform2D(), Color(), imgtex.get_rid());
	}
}

void native_imgui::setvalue(String field, RID parent) {

}

void native_imgui::Begin(String name, bool open) {
	ImGui::Begin(convertStringToChar(name), &open); // ImGuiWindowFlags_Popup Bör tas bort 
}

bool native_imgui::BeginChild(unsigned int ImGuiID, Vector2 vec, bool border) {
	return ImGui::BeginChild(ImGuiID, ImVec2ToVector2(vec), border);
}

void native_imgui::EndChild() {
	ImGui::EndChild();
}

bool native_imgui::BeginChildFrame(unsigned int ImGuiID, Vector2 vec) {
	return ImGui::BeginChildFrame(ImGuiID, ImVec2ToVector2(vec));
}

void native_imgui::EndChildFrame() {
	ImGui::EndChildFrame();
}

bool native_imgui::BeginCombo(String label, String preview) {
	return ImGui::BeginCombo(convertStringToChar(label), convertStringToChar(preview));
}

void native_imgui::EndCombo() {
	ImGui::EndCombo();
}

bool native_imgui::BeginPopup(String str_id) {
	return ImGui::BeginPopup(convertStringToChar(str_id), ImGuiWindowFlags_Popup);
}

void native_imgui::EndPopup() {
	ImGui::EndPopup();
}

bool native_imgui::BeginPopupContextItem(String str_id) {
	return ImGui::BeginPopupContextItem(convertStringToChar(str_id));
}

bool native_imgui::BeginPopupContexVoid(String str_id) {
	return ImGui::BeginPopupContextVoid(convertStringToChar(str_id));
}

bool native_imgui::BeginPopupContextWindow(String str_id) {
	return ImGui::BeginPopupContextWindow(convertStringToChar(str_id));
}

void  native_imgui::BeginGroup() {
	ImGui::BeginGroup();
}

void native_imgui::EndGroup() {
	ImGui::EndGroup();
}

bool native_imgui::BeginPopupModal(String label, bool open) {
	ImGui::BeginPopupModal(convertStringToChar(label), &open);
	return open;
}

bool native_imgui::BeginTabBar(String str_id) {
	return ImGui::BeginTabBar(convertStringToChar(str_id));
}

bool native_imgui::BeginTabBarItem(String label, bool open) {
	ImGui::BeginTabItem(convertStringToChar(label), &open);
	return open;
}

void native_imgui::EndTabBarItem() {
	ImGui::EndTabItem();
}

void native_imgui::EndTabBar() {
	ImGui::EndTabBar();
}

void native_imgui::BeginTooltip() {
	ImGui::BeginTooltip();
}


Variant native_imgui::BulletTextV(const Variant **p_args, int p_argcount, Variant::CallError &r_error) {
	String arg;
	for (uint32_t i = 0; i < p_argcount; i++) {
		if (p_args[i]->get_type() != Variant::STRING) {
			r_error.error = Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
			r_error.argument = 0;
			r_error.expected = Variant::STRING;
			return Variant();
		}
		// We conver the variant into a string and concatianate it to a godot string
		arg += (String)*p_args[i];
	}

	// We fool ImGui that we are variadic. We are converting a const char * to a char*
	//which kinda means we are praying that ImGui doens't do anything stupid
	ImGui::BulletTextV(convertStringToChar(arg), (char*)convertStringToChar(arg));
	
	r_error.error = Variant::CallError::CALL_OK;
	return Variant();
}

bool native_imgui::Button(String text, Vector2 size) {
	bool newState = ImGui::Button(convertStringToChar(text), ImVec2ToVector2(size));

	return handleButtonDic(text, newState);
}

Array native_imgui::CalcListClipping(uint32_t item_count, uint32_t item_height) {
	int out_item_display_start, out_item_display_end;
	ImGui::CalcListClipping(item_count, item_height, &out_item_display_start, &out_item_display_end);

	Array result;
	result.push_back(out_item_display_start);
	result.push_back(out_item_display_end);

	return result;
}

void native_imgui::Text(String text) {
	ImGui::Text(convertStringToChar(text));
}

void native_imgui::BulletText(String text) {
	ImGui::BulletText(convertStringToChar(text));
}

void native_imgui::End() {
	ImGui::End();
}

void native_imgui::Separator() {
	ImGui::Separator();
}

void native_imgui::Render() {
	ImGui::Render();
	ImDrawData *draw_dat = ImGui::GetDrawData();

	// validate data
	if (!draw_dat->Valid) {
		print_error("IMGUI: DRAW DATA NOT VALID");
		return;
	}

	process_imgui();
}

void native_imgui::EndFrame() {
	ImGui::EndFrame();
}

void native_imgui::NewFrame() {
	ImGui::NewFrame();
}

void native_imgui::BeginMenu(String name) {
	ImGui::BeginMenu(convertStringToChar(name));
}

void native_imgui::BeginMainMenuBar() {
	ImGui::BeginMainMenuBar();
}

void native_imgui::EndMainMenuBar() {
	ImGui::EndMainMenuBar();
}

void native_imgui::EndMenu() {
	ImGui::EndMenu();
}

bool native_imgui::MenuItem(String label, String shortcut, bool selected, bool enabled) {
	bool newState = ImGui::MenuItem(convertStringToChar(label),
			convertStringToChar(shortcut),
			selected,
			enabled);

	return handleButtonDic(label, newState);
}

float native_imgui::InputFloat(String label, float value, float step, float fastStep, String format) {
	ImGui::InputFloat(convertStringToChar(label), &value, step, fastStep, convertStringToChar(format));
	return value;
}

void native_imgui::SameLine() {
	ImGui::SameLine();
}

float native_imgui::DragFloat(String label, float value, float speed, float min, float max, String format, float power) {
	ImGui::DragFloat(convertStringToChar(label), &value, speed, min, max, convertStringToChar(format), power);
	return value;

}

Color native_imgui::ColorPicker3(String label, Color color) {
	float test[3] = { color.r, color.g, color.b };
	ImGui::ColorPicker3(convertStringToChar(label), test);
	return Color(test[0], test[1], test[2]);
	
}

bool  native_imgui::ArrowButton(String label, int dir) {
	return ImGui::ArrowButton(convertStringToChar(label), ImGuiDir_Right);
}

void native_imgui::Bullet() {
	ImGui::Bullet();
}

void native_imgui::CalcItemWidth() {
	ImGui::CalcItemWidth();
}

bool native_imgui::CheckBox(String label, bool val) {
	ImGui::Checkbox(convertStringToChar(label), &val);
	return val;
}

void native_imgui::CloseCurrentPopup() {
	ImGui::CloseCurrentPopup();
}

bool native_imgui::ColorButton(String desc_id, Color vec) {
	ImVec4 _vec(vec.r, vec.g, vec.b, 1.0);
	bool newState = ImGui::ColorButton(convertStringToChar(desc_id), _vec);
	return handleButtonDic(desc_id, newState);
}

Color native_imgui::ColorEdit3(String label, Color vec) {
	float _vec[3] = { vec.r, vec.g, vec.b };
	ImGui::ColorEdit3(convertStringToChar(label), _vec);

	return Color(_vec[0], _vec[1], _vec[2]);
}

void native_imgui::RebuildFontAtlas() {


}

native_imgui::native_imgui() {
	this->VisualServer = VisualServer::get_singleton();
	context = ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	ImGui::SetCurrentContext(context);
	ImGui::StyleColorsDark();
	io.Fonts->AddFontDefault();
	io.MouseDrawCursor = true;
	io.BackendFlags = 0; 

	int width, height, bytesPerPixel;
	unsigned char *pixels = NULL;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &bytesPerPixel);

	PoolByteArray textureDataRaw;

	for (uint32_t i = 0; i < width * height * bytesPerPixel; i++) {
		textureDataRaw.push_back(pixels[i]);
	}

	Image img(width, height, false, Image::Format::FORMAT_RGBA8, textureDataRaw); 

	imgtex.create_from_image(img.duplicate(), 0);

	io.Fonts->TexID = ImTextureID(100);

	io.Fonts->ClearTexData();


	io.DisplaySize.x = GLOBAL_GET("display/window/size/width"); // set the current display width
	io.DisplaySize.y = GLOBAL_GET("display/window/size/height"); // set current display height

 
}
