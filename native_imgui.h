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
	 

protected:
	static void _bind_methods();
	virtual void _process(float delta, RID parent); 
	Vector<Array> extract_imgui_data();
	void Render(float delta, ImDrawData *draw_data, RID parent);

public: 
	void RebuildFontAtlas();
	native_imgui();
};

#endif
