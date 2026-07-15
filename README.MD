# CppWebUI

CppWebUI is a proof-of-concept C++ server-driven web UI framework inspired by projects like NiceGUI.

The goal is to let a C++ application define a browser-based interface directly from C++ code. The server owns the UI state, while the browser acts as a lightweight display and input layer connected through WebSockets.

This project is experimental and currently intended for learning, prototyping, and exploring how a NiceGUI-style programming model could work in modern C++.

## Example

```cpp
#include <string>

import UI;

auto main() -> int
{
	auto app = ui::App{};

	auto counter = 0;

	app.RegisterPage("/", [&]( ui::PageBuilder<> ui ) {
		auto* label1 = ui.Heading( "Test" );
		label1->text = "test";

		auto* modal = ui.Modal( []( auto ui, ui::dom::Modal* modal ) {
			ui.Card( [modal]( auto ui ){
				ui.Header( []( auto ui ){
					ui.Paragraph( "This is header" );
				} );

				ui.Paragraph( "This is body" );

				ui.Footer( [modal]( auto ui ) {
					ui.Paragraph( "This is footer" );

					ui.Button( "Close", [modal]{
						if( modal )
						{
							modal->open = false;
						}
					} );
				} );
			} );
		} );

		ui.Container( []( auto ui ) {
			ui.Label( "Test2" );
		} );

		ui.Container( [label1, modal, &counter]( auto ui ) {
			ui.Button( "Click me!", [label1, modal, &counter]{
				counter++;

				// label1->text is a custom property type with getters and
				// setters, so setting it updates the browser immediately.
				label1->text = "Clicked times: " + std::to_string( counter );

				if( modal )
				{
					modal->open = true;
				}
			} );
		} );

		ui.HorizontalRule();
	} );

	app.Run();

	return 0;
}
```

## Concept

CppWebUI uses a server-driven UI model:

```text
HTTP GET /
    -> server returns template.html

Browser opens WebSocket
    -> browser sends current route path

Server receives route path
    -> server finds the registered page
    -> server builds the server-side DOM tree
    -> server sends DOM operations to the browser

Browser event occurs
    -> browser sends event message to server

Server handles event
    -> server updates UI state
    -> server sends updates back to the browser
```

This allows common UI behavior to be written in C++, without manually writing large amounts of JavaScript.

## Current Features

* C++ module-based structure
* Drogon-based HTTP and WebSocket server
* Server-side page registration
* Server-side DOM tree representation
* Lightweight scoped page builder handles
* Basic DOM element creation and deletion
* Text and attribute updates
* Button click events from browser to server
* Change and submit event plumbing
* Reactive-style property updates
* Basic card and modal support
* Static browser assets served from the `www` directory

## Current Architecture

The application is centered around `ui::App`.

`ui::App` is responsible for:

* loading the Drogon configuration
* registering pages
* starting the server
* coordinating page creation and client connections

Pages are registered with a builder function:

```cpp
app.RegisterPage( "/", []( ui::PageBuilder<> ui ){
	ui.Heading( "Hello" );

	ui.Button( "Click me", []{
		// server-side callback
	} );
} );
```

`ui::PageBuilder<>` is a lightweight scoped builder handle. It points to the underlying server-side page-building context and the current parent element.

Child-builder functions receive their own scoped builder:

```cpp
ui.Container( []( auto ui ){
	ui.Label( "Inside container" );
	ui.Button( "Click", []{
		// server-side callback
	} );
} );
```

This makes it possible to create elements inside the correct parent during the initial page build, and also allows scoped builders to be captured for later dynamic UI updates.

Builder functions return pointers to server-side DOM elements. These elements are owned by the server-side DOM tree and are intended to have stable addresses for the lifetime of the client page.

This makes it possible to capture element pointers in callbacks:

```cpp
app.RegisterPage( "/", []( ui::PageBuilder<> ui ){
	auto* label = ui.Label( "Waiting..." );

	ui.Button( "Update", [label]{
		label->text = "Updated from C++";
	} );
} );
```

Elements with child builders can optionally expose the parent element to the builder. This is useful for components such as modals:

```cpp
auto* modal = ui.Modal( []( auto ui, ui::dom::Modal* modal ){
	ui.Card( [modal]( auto ui ){
		ui.Paragraph( "Modal body" );

		ui.Button( "Close", [modal]{
			modal->open = false;
		} );
	} );
} );

ui.Button( "Open modal", [modal]{
	modal->open = true;
} );
```

## Browser Protocol

CppWebUI communicates with the browser using JSON messages over WebSockets.

Example browser-to-server message:

```json
{
	"op": "on_click",
	"id": "button-uuid"
}
```

Example server-to-browser message:

```json
{
	"op": "create_element",
	"parent_id": "root",
	"id": "label-uuid",
	"tag": "div"
}
```

Example text update:

```json
{
	"op": "set_text",
	"id": "label-uuid",
	"text": "Clicked times: 1"
}
```

Example modal update:

```json
{
	"op": "set_modal_open",
	"id": "modal-uuid",
	"open": true
}
```

The protocol is intentionally simple for now and is expected to change as the framework design develops.

## Dependencies

CppWebUI currently uses:

* C++20/C++23
* Drogon
* JsonCpp
* CMake
* a compiler with usable C++ module support

The project has been developed while experimenting with modern C++ modules, so compiler and build-system support may still be fragile depending on the environment.

## Development Status

This project is currently a proof of concept.

Working so far:

* registering a page from C++
* serving an HTML template
* opening a WebSocket connection
* sending DOM creation messages to the browser
* sending browser events back to the server
* updating server-side UI state
* pushing updates back to the browser
* basic modal open and close behavior
* scoped child builders for nested UI construction

Still experimental:

* page lifecycle management
* client connection ownership
* DOM diffing and patching
* event routing
* reconnect behavior
* routing
* styling
* build system portability

## Possible Future Features

Potential future ideas include:

* reusable components
* layouts
* typed events
* DOM patch batching
* automatic reconnection
* input elements
* forms
* tables
* charts
* authentication helpers
* Drogon plugin integration
* hot reload during development

## Why?

For internal tools, dashboards, simulations, game-engine tooling, trading tools, and server-side control panels, a C++ server-driven UI could be useful.

This project is an experiment to see how far that idea can go.

## License

CppWebUI is released under the MIT License.
