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
	Image img;
	ImageTexture imgtex;
	RID newChild; // unused
	
	ArrayMesh mesh;
	
	List<RID> children;
	List<ArrayMesh*> meshes;
	Dictionary loadedTextures;

	VisualServer *VisualServer;
	ImGuiContext *context;

	Dictionary buttonDict;
	Dictionary floatDict;

	String input;

	/* Helper functions for conversion between libs */
	bool handleButtonDic(String label, bool newState);
	inline const char *convertStringToChar(String string);
	inline ImVec2 Vector2ToImVec(const Vector2& vec); 
	inline Vector2 ImVec2ToVector2(const ImVec2 &vec);
	inline Color ImVec4ToColor(const ImVec4 &vec);
	float valuesGetter(void *data, int idx);

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
	Vector2 CalcTextSize(String text, String end);
	void CaptureKeyboardFromApp(bool capture);
	void CaptureMouseFromApp(bool capture);
	bool CheckboxFlags(String label, uint32_t flags, uint32_t flags_value);
	bool CollapsingHeader(String label); // Kanske dic på denna?
	void CalcItemWidth();
	bool CheckBox(String label, bool val);
	void CloseCurrentPopup();

	bool ColorButton(String desc_id, Color vec);
	Color ColorPicker3(String label, Color color);

	Color ColorPicker4(String label, Color color);
	Color ColorEdit3(String label, Color vec);
	Color ColorEdit4(String label, Color vec);
	float DragFloat(String label, float value, float speed, float min, float max, float power);
	void Dummy(Vector2 vec);
	String GetClipboardText();
	uint32_t GetColumnIndex();
	void  GetColumnOffset(int index);
	void GetColumnsCount();
	void GetColumnWidth(int index);
	Vector2 GetContentRegionAvail();
	float GetContentRegionAvailWidth();
	Vector2 GetContentRegionMax();
	Vector2 GetCursorPos();
	float GetCursorPosX();
	float GetCursorPosY();
	Vector2 GetCursorScreenPos();
	Vector2 GetCursorStartPos();
	void GetFont();
	float GetFontSize();
	Vector2 GetFontTexUvWhitePixel();
	float GetFrameCount();
	float GetFrameHeight();
	float GetFrameHeightWithSpacing();
	Vector2 GetItemRectMax();
	Vector2 GetItemRectMin();
	Vector2 GetItemRectSize();
	int GetKeyIndex(int key);
	int GetKeyPressedAmount(int key, float repeat_delay, float rate);
	int GetMouseCursor();
	Vector2 GetMouseDragDelta();
	Vector2 GetMousePos();
	Vector2 GetMousePosOnOpeningCurrentPopup();
	float GetScrollMaxX();
	float GetScrollMaxY();
	float GetScrollX();
	float GetScrollY();
	int GetStyle();
	String GetStyleColorName(int idx);
	Color GetStyleColorVec4(int idx);
	float GetTextLineHeight();
	float GetTextLineHeightWithSpacing();
	float GetTime();
	float GetTreeNodeToLabelSpacing();
	Vector2 GetWindowContentRegionMax();
	Vector2 GetWindowContentRegionMin();
	float GetWindowContentRegionWidth();
	float GetWindowHeight();
	float GetWindowWidth();
	Vector2 GetWindowPos();
	Vector2 GetWindowSize();

	int GetID(String id);
	void Indent(float indent_width);
	double InputDouble(String label, double value, double step, double faststep, String format);
	float InputFloat(String label, float value, float step, float faststep, String format);
	Vector2 InputFloat2(String label, Vector2 value, String format);
	Vector3 InputFloat3(String label, Vector3 value, String format);
	Color InputFloat4(String label, Color, String format);
	int InputInt(String label, int value, int step, int step_fast);
	Vector2 InputInt2(String label, Vector2 value, int step, int step_fast);
	Vector3 InputInt3(String label, Vector3 value, int step, int step_fast);
	/*Vector4 InputInt4(String label, int value, Vector4 step, int step_fast); */
	float InputScalar(String label, unsigned int datatype, int val, unsigned int step, unsigned int faststep); // This one might be something we have to live without
	String InputText(String label, String val, unsigned int flags); // behaves weird with label and value swapping during frames. Same memory adress?
	String InputTextMultiline(String label, String val, unsigned int buf_size, Vector2 size); // behaves weird with label and value swapping during frames. Same memory adress?
	String InputTextWithHint(String label, String hint, String val, unsigned int buf_size);
	bool InvisibleButton(String str_id, Vector2 size);
	bool IsAnyItemActive();
	bool IsAnyItemFocused();
	bool IsAnyItemHovered();
	bool IsAnyMouseDown();
	bool IsItemActivated();
	bool IsItemClicked();
	bool IsItemDeactivated();
	bool IsItemDeactivatedAfterChange();
	bool IsItemDeactivatedAfterEdit();
	bool IsItemEdited();
	bool IsItemFocused();
	bool IsItemHovered();
	bool IsItemToggledOpen();
	bool IsItemVisible();
	bool IsKeyDown(unsigned int key_index);
	bool IsKeyReleased(unsigned int key_index);
	bool IsKeyPressed(unsigned int key_index);
	bool IsMouseClicked(unsigned int button);
	bool IsMouseDoubleClicked(unsigned int button);
	bool IsMouseDown(unsigned int button);
	bool IsMouseDragging(unsigned int button);
	bool IsMouseHoveringRect(Vector2 min, Vector2 max, bool clip);
	bool IsMousePosValid(Vector2 pos);
	bool IsMouseReleased(unsigned int button);
	bool IsPopupOpen(String str_id);
	bool IsRectVisible(const Vector2 &vec);
	bool IsWindowAppearing();
	bool IsWindowCollapsed();
	bool IsWindowFocused();
	bool IsWindowHovered();
	Variant LabelText(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	Variant LabelTextV(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	void ListBox(String label, int currentItem, Array items);
	void ListBoxFooter();
	bool ListBoxHeader(String label, Vector2 size);
	void LogButtons();
	void LogFinish();
	Variant LogText(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	void LogToClipboard();
	void NextColumn();
	void OpenPopup(String str_id);
	void OpenPopupContextItem(String str_id);
	void OpenPopupOnItemClick(String str_id);
	void PlotHistogram(String label, Vector<float> arr);
	void PlotLines(String label, Vector<float> arr);
	void PopAllowKeyboardFocus();
	void PopButtonRepeat();
	void PopClipRect();
	void PopFont();
	void PopID();
	void PopItemWidth();
	void PopStyleColor();
	void PopStyleVar();
	void PopTextWrapPos();
	void ProgressBar(float fraction, Vector2 size);
	void PushAllowKeyboardFocus(bool allow_keyboard_focus);
	void PushButtonRepeat(bool repeat);
	void PushClipRect(Vector2 max, Vector2 min, bool intersects_with_current_rect);
	void PushFont();
	void PushID(int int_id);
	void PushItemWidth(float item_width);
	void PushStyleColor(int idx, Color col);
	void PushStyleVar(int idx, Vector2 vec);
	void PushTextWrapPos(float wrap_local_pos_x);
	bool RadioButton(String label, bool active);
	bool Selectable(String label, bool active);
	void SetClipboardText(String text);
	void SetColorEditOptions(int flags);
	void SetColumnOffset(int column_index, int offset);
	void SetColumnWidth(int column_index, float width);
	void SetCursorPos(Vector2 pos);
	void SetCursorPosX(float x);
	void SetCursorPosY(float y);
	void SetCursorScreenPos(Vector2 pos);
	void SetItemAllowOverlap();
	void SetItemDefaultFocus();
	void SetKeyboardFocusHere(int offset);
	void SetMouseCursor(int cursor);
	void SetNextItemOpen(bool is_open, int condition);
	void SetNextItemWidth(float width);
	void SetNextTreeNodeOpen(bool open, int condition);
	void SetNextWindowBgAlpha(float alpha);
	void SetNextWindowCollapsed(bool collapsed, int cond);
	void SetNextWindowContentSize(Vector2 size);
	void SetNextWindowFocus();
	void SetNextWindowPos(Vector2 pos, int cond, Vector2 pivot);
	void SetNextWindowSize(Vector2 size, int cond);
	void SetNextWindowSizeConstraints(Vector2 min, Vector2 max);
	void SetScrollFromPosX(float x);
	void SetScrollFromPosY(float y);
	void SetScrollHere(float center_ratio); // OBSOLETE
	void SetScrollHereX(float center_x_ratio);
	void SetScrollHereY(float center_y_ratio);
	void SetScrollX(float x);
	void SetScrollY(float y);
	void SetTabItemClosed(String label);
	Variant SetTooltip(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	Variant SetTooltipV(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	void SetWindowCollapsed(bool collapsed, int cond);
	void SetWindowFocus();
	void SetWindowFontScale(float scale);
	void SetWindowPos(Vector2 pos, int cond);
	void SetWindowSize(Vector2 size, int cond);
	void ShowFontSelector(String label);
	float SliderAngle(String label, float angle);
	float SliderFloat(String label, float value, float max, float min);
	Vector2 SliderFloat2(String label, Vector2 values, float min, float max);
	Vector3 SliderFloat3(String label, Vector3 values, float min, float max);
	Color SliderFloat4(String label, Color values, float min, float max);
	int SliderInt(String label, int val, int min, int max);
	Vector2 SliderInt2(String label, Vector2 val, int min, int max);
	Vector3 SliderInt3(String label, Vector3 val, int min, int max);
	Color SliderInt4(String label, Color val, int min, int max);
	bool SmallButton(String label);
	void Spacing();
	void StyleColorsClassic();
	void StyleColorsDark();
	void StyleColorsLight();
	Variant TextDisabled(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	Variant Text(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	Variant TextWrapped(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	Variant TextColored(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	void TreeAdvanceToLabelPos();
	void TreeNode(String label);
	void TreeNodeEx(String label, int flags);
	Variant TreeNodeExV(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	Variant TreeNodeV(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	void TreePop();
	void TreePush();
	void Unindent(float width);
	void Value(String id, unsigned int value);
	float VSliderFloat(String label, Vector2 size, float val, float min, float max);
	int VSliderInt(String label, Vector2 size, int val, int min, int max);

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
	void SameLine();
	//float DragFloat(String label, float value, float speed, float min, float max, String format, float power); // Too many args for bind_method
	bool ArrowButton(String label, int dir);
	void Bullet();
};

#endif
