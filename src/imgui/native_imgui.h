#ifndef NATIVE_IMGUI_H
#define NATIVE_IMGUI_H

#include <stdarg.h>

#include "imgui.h"

#include "core/reference.h"

#include "../../servers/visual_server.h"
#include "../../core/os/keyboard.h"
#include "../../core/os/os.h"
#include "../../core/os/input.h"
#include "core/vector.h"
#include "scene/gui/control.h"

#include <vector>
#include <map>
#include <string>

// _inpu
class native_imgui : public Control {
	GDCLASS(native_imgui, Control);
	
	//uint32_t *fontTextureId = nullptr;
	static int mouseWheel;
	ImageTexture imgtex; // This can't be static, and thats fine. as texture count is static, it will behave like it
	static uint32_t textureCount;
	static VisualServer *VisualServer;
	static ImGuiContext *context;

	static uint32_t currPos;
	static uint32_t limit;
	static char *charbuff;
	static std::vector<char *> strings;
	static std::vector<int> posStrings;
	Vector<Vector<ArrayMesh*>> meshDict;
	Vector<Vector<RID>> childDict;
	Dictionary buttonDict;
	Dictionary floatDict;
	Dictionary Rect; 

	std::map<String, std::vector<char>> input; 
	
	 

	/* Helper functions for conversion between libs */
	char * handleInputString(String label, String val, int capacity); 
	bool handleButtonDic(String label, bool newState); 
	const char *convertStringToChar(const String string);
	inline ImVec2 Vector2ToImVec(const Vector2& vec); 
	inline Vector2 ImVec2ToVector2(const ImVec2 &vec);
	inline Color ImVec4ToColor(const ImVec4 &vec);
	float valuesGetter(void *data, int idx);
	unsigned int FixKey(KeyList kc);
	 
	virtual void process_imgui();  
	void draw();

protected: 
	// Godot functions
	static void _bind_methods();

public: 
	virtual bool _input(const Ref<InputEvent> &evt);
	void RebuildFontAtlas();
	native_imgui();
	~native_imgui();
	 

	/*IMGUI WRAPPER */
	void Begin(String name, bool open, int flags);
	bool BeginChild(unsigned int ImGuiID, Vector2 vec, bool border, int flags);
	void EndChild();
	bool BeginChildFrame(unsigned int ImGuiID, Vector2 vec, int flags);
	void EndChildFrame();
	bool BeginCombo(String label, String preview, int flags); // Problem med flags
	void EndCombo();
	bool BeginPopup(String str_id, int flags); // problem med flags
	void EndPopup();
	bool BeginPopupContextItem(String str_id, int flags);
	bool BeginPopupContexVoid(String str_id, int flags);
	bool BeginPopupContextWindow(String str_id, int flags);
	bool BeginMenuBar();
	void BeginGroup(); // Assertion failed: window->Flags & ImGuiWindowFlags_Popup
	void EndGroup();
	void EndMenuBar();
	bool BeginPopupModal(String label, bool open, int flags); // problem med flags
	bool BeginTabBar(String str_id, int flags); // Assertion failed: window->Flags & ImGuiWindowFlags_Popup
	bool BeginTabBarItem(String label, bool open, int flags);
	void EndTabBarItem();
	void EndTabBar();
	void BeginTooltip(); 
	bool Button(String text, Vector2 size);
	Array CalcListClipping(uint32_t item_count, uint32_t item_height);
	Vector2 CalcTextSize(String text, String end, bool hide_text, float wrap_width);
	void CaptureKeyboardFromApp(bool capture);
	void CaptureMouseFromApp(bool capture);
	bool CheckboxFlags(String label, uint32_t flags, uint32_t flags_value);
	bool CollapsingHeader(String label, int flags); // Kanske dic på denna?
	void CalcItemWidth();
	bool CheckBox(String label, bool val);
	void CloseCurrentPopup();
	bool ColorButton(String desc_id, Color vec, int flags, Vector2 size);
	Color ColorPicker3(String label, Color color, int flags);
	Color ColorPicker4(String label, Color color, int flags);
	Color ColorEdit3(String label, Color vec, int flags);
	Color ColorEdit4(String label, Color vec, int flags);
	float DragFloat(String label, float value, float speed, float min, float max, String format, float power);
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
	double InputDouble(String label, double value, double step, double faststep, String format, int flags);
	float InputFloat(String label, float value, float step, float faststep, String format, int flags);
	Vector2 InputFloat2(String label, Vector2 value, String format, int flags);
	Vector3 InputFloat3(String label, Vector3 value, String format, int flags);
	Color InputFloat4(String label, Color, String format, int flags);
	int InputInt(String label, int value, int step, int step_fast, int flags);
	Vector2 InputInt2(String label, Vector2 value, int flags);
	Vector3 InputInt3(String label, Vector3 value, int flags);
	/*Vector4 InputInt4(String label, int value, Vector4 step, int step_fast); */
	float InputScalar(String label, unsigned int datatype, int val, unsigned int step, unsigned int faststep); // This one might be something we have to live without

	String InputText(String label, String val, int capacity, int flags);
	String InputTextMultiline(String label, String val, Vector2 size, int capacity, int flags); // behaves weird with label and value swapping during frames. Same memory adress?
	String InputTextWithHint(String label, String hint, String val, int capacity, int flags);
	bool InvisibleButton(String str_id, Vector2 size, int flags);
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
	bool IsMouseClicked(unsigned int button, bool repeat);
	bool IsMouseDoubleClicked(unsigned int button);
	bool IsMouseDown(unsigned int button);
	bool IsMouseDragging(unsigned int button, float lock_threshold);
	bool IsMouseHoveringRect(Vector2 min, Vector2 max, bool clip);
	bool IsMousePosValid(Vector2 pos);
	bool IsMouseReleased(unsigned int button);
	bool IsPopupOpen(String str_id, int flags);
	bool IsRectVisible(const Vector2 &vec);
	bool IsWindowAppearing();
	bool IsWindowCollapsed();
	bool IsWindowFocused();
	bool IsWindowHovered();
	Variant LabelText(const Variant **p_args, int p_argcount, Variant::CallError &r_error); 
	void ListBox(String label, int currentItem, Array items);
	void ListBoxFooter();
	bool ListBoxHeader(String label, Vector2 size);
	void LogButtons();
	void LogFinish();
	Variant LogText(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	void LogToClipboard();
	void NextColumn();
	void OpenPopup(String str_id, int flags);
	void OpenPopupContextItem(String str_id, int button);
	void OpenPopupOnItemClick(String str_id, int flags);
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
	void ProgressBar(float fraction, Vector2 size, String overlay);
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
	bool Selectable(String label, bool active, int flags, Vector2 size);
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
	void SetScrollFromPosX(float x, float center_ratio);
	void SetScrollFromPosY(float y, float center_ratio);
	void SetScrollHere(float center_ratio); // OBSOLETE
	void SetScrollHereX(float center_x_ratio);
	void SetScrollHereY(float center_y_ratio);
	void SetScrollX(float x);
	void SetScrollY(float y);
	void SetTabItemClosed(String label);
	Variant SetTooltip(const Variant **p_args, int p_argcount, Variant::CallError &r_error); 
	void SetWindowCollapsed(bool collapsed, int cond);
	void SetWindowFocus();
	void SetWindowFontScale(float scale);
	void SetWindowPos(Vector2 pos, int cond);
	void SetWindowSize(Vector2 size, int cond);
	void ShowFontSelector(String label);
	float SliderAngle(String label, float angle, float min, float max, String format, int flags);
	float SliderFloat(String label, float value, float max, float min, String format, int flags);
	Vector2 SliderFloat2(String label, Vector2 values, float min, float max, String format, int flags);
	Vector3 SliderFloat3(String label, Vector3 values, float min, float max, String format, int flags);
	Color SliderFloat4(String label, Color values, float min, float max, String format, int flags);
	int SliderInt(String label, int val, int min, int max, String format, int flags);
	Vector2 SliderInt2(String label, Vector2 val, int min, int max, String format, int flags);
	Vector3 SliderInt3(String label, Vector3 val, int min, int max, String format, int flags);
	Color SliderInt4(String label, Color val, int min, int max, String format, int flags);
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
	bool TreeNode(String label); 
	void TreePop();
	void TreePush();
	void Unindent(float width);
	void Value(String id, unsigned int value);
	float VSliderFloat(String label, Vector2 size, float val, float min, float max, String format, int flags);
	int VSliderInt(String label, Vector2 size, int val, int min, int max, String format, int flags);
	Variant BulletText(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	void End();
	void Separator();
	void Render();
	void EndFrame();
	void NewFrame();
	void BeginMenu(String name, bool enabeld);
	void BeginMainMenuBar();
	void EndMainMenuBar();
	void EndMenu();
	bool MenuItem(String label, String shortcut, bool  selected, bool enabled);
	void SameLine(float offset_from_start, float spacing);
	//float DragFloat(String label, float value, float speed, float min, float max, String format, float power); // Too many args for bind_method
	bool ArrowButton(String label, int dir);
	void Bullet();
};

// Making sure Godot can handle our binds for our enums
VARIANT_ENUM_CAST(ImGuiWindowFlags_);
VARIANT_ENUM_CAST(ImGuiInputTextFlags_);
VARIANT_ENUM_CAST(ImGuiTreeNodeFlags_);
VARIANT_ENUM_CAST(ImGuiPopupFlags_);
VARIANT_ENUM_CAST(ImGuiSelectableFlags_);
VARIANT_ENUM_CAST(ImGuiComboFlags_);
VARIANT_ENUM_CAST(ImGuiTabBarFlags_);
VARIANT_ENUM_CAST(ImGuiTabItemFlags_);
VARIANT_ENUM_CAST(ImGuiHoveredFlags_);
VARIANT_ENUM_CAST(ImGuiFocusedFlags_);
VARIANT_ENUM_CAST(ImGuiDragDropFlags_);
VARIANT_ENUM_CAST(ImGuiDataType_);
VARIANT_ENUM_CAST(ImGuiDir_);
VARIANT_ENUM_CAST(ImGuiKey_)
VARIANT_ENUM_CAST(ImGuiKeyModFlags_)
VARIANT_ENUM_CAST(ImGuiNavInput_)
VARIANT_ENUM_CAST(ImGuiConfigFlags_)
VARIANT_ENUM_CAST(ImGuiBackendFlags_)
VARIANT_ENUM_CAST(ImGuiCol_)
VARIANT_ENUM_CAST(ImGuiStyleVar_)
VARIANT_ENUM_CAST(ImGuiButtonFlags_)
VARIANT_ENUM_CAST(ImGuiColorEditFlags_)
VARIANT_ENUM_CAST(ImGuiSliderFlags_)
VARIANT_ENUM_CAST(ImGuiMouseButton_)
VARIANT_ENUM_CAST(ImGuiMouseCursor_)
VARIANT_ENUM_CAST(ImGuiCond_)

#endif
