#include "wmmm.hpp"
#include <glog/logging.h>

std::unique_ptr<WMMM> WMMM::create (const std::string& display) {

	// 1. Establish connection to X server
	const char* display_str = display.empty() ? nullptr : display.c_str();

	xcb_connection_t *c_ = xcb_connect(display_str, nullptr);

	if (xcb_connection_has_error(c_)) {

		LOG(ERROR) << "Error: cannot connect to X display " << display << ".";

		return nullptr;

	}

	// 2. Construct WMMM instance
	return std::unique_ptr<WMMM>(new WMMM(c_));

}

WMMM::WMMM (xcb_connection_t *c):	c(CHECK_NOTNULL(c)),
					screen(xcb_setup_roots_iterator(xcb_get_setup(c)).data),
					cmap(screen->default_colormap)
					{}

WMMM::~WMMM () {

	xcb_disconnect(c);

}

void WMMM::run () {

		//  TODO: Consider using a "super-frame" window that allthe other windows are children of?
		//  Or do we just expose the naked root window to the user?

		// 1. Setting up: Select events on root window

		uint32_t values[] = {	XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT |
					XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY   |
					XCB_EVENT_MASK_PROPERTY_CHANGE       |
					XCB_EVENT_MASK_KEY_PRESS             };

		xcb_generic_error_t *err = xcb_request_check(c,
							xcb_change_window_attributes_checked(c,
								screen->root,
								XCB_CW_EVENT_MASK,
								values));

		LOG_IF(INFO, err == nullptr) << "yay";

}
