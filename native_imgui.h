#ifndef NATIVE_IMGUI_H
#define NATIVE_IMGUI_H

#include <stdarg.h>

#include "imgui.h"

#include "core/reference.h"

#include "../../servers/visual_server.h"

#include "core/vector.h"
#include "scene/2d/node_2d.h"

class native_imgui : public Node2D {
	GDCLASS(native_imgui, Node2D);

	int count;
	uint32_t *fontTextureId = nullptr;
	VisualServer *VisualServer;
	List<RID> children;
	List<ArrayMesh*> meshes;
	Dictionary loadedTextures;
	ImageTexture imgtex;
	RID newChild;
	ImGuiContext *context;

	
	 
	Image img;
	ArrayMesh mesh;
	Dictionary buttonDict;
	Dictionary floatDict;

	bool handleButtonDic(String label, bool newState);
	inline const char *convertStringToChar(String string);
	inline ImVec2 ImVec2ToVector2(const Vector2& vec);

protected:
	static void _bind_methods();
	virtual void process_imgui(); 
	Vector<Array> extract_imgui_data();
	void draw();


public:
	void RebuildFontAtlas();
	native_imgui();

	void setvalue(String field, RID parent);

	/*IMGUI WRAPPER */
	void Begin(String name, bool open);
	bool BeginChild(unsigned int ImGuiID, Vector2 vec, bool border);
	void EndChild();
	bool BeginChildFrame(unsigned int ImGuiID, Vector2 vec);
	void EndChildFrame();
	bool BeginCombo(String label, String preview); // Problem med flags
	void EndCombo();
	bool BeginPopup(String str_id); // problem med flags
	void EndPopup();
	bool BeginPopupContextItem(String str_id);
	bool BeginPopupContexVoid(String str_id);
	bool BeginPopupContextWindow(String str_id);
	void BeginGroup(); // Assertion failed: window->Flags & ImGuiWindowFlags_Popup
	void EndGroup();
	bool BeginPopupModal(String label, bool open); // problem med flags
	bool BeginTabBar(String str_id); // Assertion failed: window->Flags & ImGuiWindowFlags_Popup
	bool BeginTabBarItem(String label, bool open);
	void EndTabBarItem();
	void EndTabBar();
	void BeginTooltip();
	Variant native_imgui::BulletTextV(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	bool Button(String text, Vector2 size);
	Array CalcListClipping(uint32_t item_count, uint32_t item_height);
	void Text(String text);
	void BulletText(String text);
	void End();
	void Separator();
	void Render();
	void EndFrame();
	void NewFrame();
	void BeginMenu(String name);
	void BeginMainMenuBar();
	void EndMainMenuBar();
	void EndMenu();
	bool MenuItem(String label, String shortcut, bool  selected, bool enabled);
	float InputFloat(String label, float value, float step, float faststep, String format);
	void SameLine();
	float DragFloat(String label, float value, float speed, float min, float max, String format, float power); // Too many args for bind_method
	
	bool ArrowButton(String label, int dir);
	void Bullet();
	void CalcItemWidth();
	bool CheckBox(String label, bool val);
	void CloseCurrentPopup();
	Color ColorPicker3(String label, Color color);
	bool ColorButton(String desc_id, Color vec);
	Color ColorEdit3(String label, Color vec);
};

#endif
