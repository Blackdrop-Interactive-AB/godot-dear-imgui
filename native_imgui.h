#ifndef NATIVE_IMGUI_H
#define NATIVE_IMGUI_H

#include "imgui.h"

#include "core/reference.h"

#include "servers/rendering_server.h"

#include "core/vector.h"
#include "scene/2d/node_2d.h"

class native_imgui : public Node2D {
	GDCLASS(native_imgui, Node2D);

	int count;
	uint32_t *fontTextureId = nullptr;
	RenderingServer *VisualServer;
	List<RID> children;
	List<ArrayMesh*> meshes;
	Dictionary loadedTextures;
	ImageTexture imgtex;

	ImGuiContext *context;


protected:
	static void _bind_methods();
	virtual void _process(float delta, RID parent);
	void Render(float delta, ImDrawData *draw_data, RID parent);

public: 
	void RebuildFontAtlas();
	native_imgui();
};

#endif
