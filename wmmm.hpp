extern "C" {

	#include <xcb/xcb.h>
	#include <xcb/xproto.h>
	#include <xcb/xcb_keysyms.h>

	#include <X11/keysym.h>

}

#include <memory>
#include <unordered_map>
#include <glog/logging.h>

class WMMM {

	public:

		// Establish a connection to the X server and create a window manager instance
		static std::unique_ptr<WMMM> create (const std::string& display = std::string());

		// Call exit routines and disconnect from the X server
		~WMMM ();

		// Entry point to the class; enter the main event loop
		void run ();

		// Invoked internally by create()
		WMMM(xcb_connection_t *c);

	private:

		// Handle to the XCB connection in use
		xcb_connection_t *c;

		// Handle to the current (default) screen of the connection
		xcb_screen_t *screen;

		// ?????? etadaavashyakam?
		// Handle to the colour map in use
		xcb_colormap_t cmap;

		// The value of the numlockmask, set after creation
		static unsigned int numlockmask;

		// Maps top-level windows to their frame windows
		std::unordered_map<uint32_t, uint32_t> clients;

};
