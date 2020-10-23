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
/*	/*
	int width = 256, height = 256, bytesPerPixel = 4;
	PoolVector<uint8_t> p_data;
	p_data.resize(width * height * bytesPerPixel);

	for (uint32_t i = 0; i < width * height * 4; i++) {
		p_data.set(i, (uint8_t)255);
	}

	img.create(width, height, false, Image::Format::FORMAT_RGBA8, p_data);

	imgtex.create_from_image(img.duplicate());
	  

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

	for (uint32_t i = 0; i < vertices.size(); i++) {
		colors.push_back(Color(0.5, 1.1, 0.4));
		indices.push_back(i);
	}

	uvs.push_back(Vector2(0, 0));
	uvs.push_back(Vector2(1, 0));
	uvs.push_back(Vector2(1, 1));

	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(0, 1));
	uvs.push_back(Vector2(0, 0));
	/*
	VisualServer->canvas_item_set_parent(newChild, parent);
	VisualServer->canvas_item_set_draw_index(newChild, 0);



	arrays.resize(ArrayMesh::ARRAY_MAX);
	arrays[(int)ArrayMesh::ArrayType::ARRAY_VERTEX] = vertices;
	arrays[(int)ArrayMesh::ArrayType::ARRAY_INDEX] = indices;

	arrays[(int)ArrayMesh::ArrayType::ARRAY_COLOR] = colors;
	arrays[(int)ArrayMesh::ArrayType::ARRAY_TEX_UV] = uvs; 
	*/

		//update();

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
