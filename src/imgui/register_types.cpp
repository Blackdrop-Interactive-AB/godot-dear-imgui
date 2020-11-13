/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "native_imgui.h"

void register_imgui_types() {
	ClassDB::register_class<native_imgui>();
}

void unregister_imgui_types() {
   // Nothing to do here in this example.
}
