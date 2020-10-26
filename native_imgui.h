#ifndef NATIVE_IMGUI_H
#define NATIVE_IMGUI_H

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
	inline ImVec2 ImVec2ToVector2(Vector2& vec);

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
	bool Button(String text, Vector2 size);
	void Text(String text);
	void BulletText(String text);
	void End();
	void Separator();
	void Render();
	void EndFrame();
	void NewFrame();
	void BeginMenu(String name);
	void EndMenu();
	bool MenuItem(String label, String shortcut, bool  selected, bool enabled);
	float InputFloat(String label, float value, float step, float faststep, String format);
	void SameLine();
	float DragFloat(String label, float value, float speed, float min, float max, String format, float power); // Too many args for bind_method
	Vector3 ColorPicker3(String label, Vector3 color);
	bool ArrowButton(String label, int dir);
	void Bullet();
	void CalcItemWidth();
	bool CheckBox(String label, bool val);
	void CloseCurrentPopup();
	bool ColorButton(String desc_id, Vector3 vec);
};

#endif
