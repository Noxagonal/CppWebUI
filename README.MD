# CppWebUI

CppWebUI is a proof-of-concept C++ server-driven web UI framework inspired by projects like NiceGUI.

The goal is to let a C++ application define a browser-based interface directly from C++ code. The server owns the UI state, while the browser acts as a lightweight display and input layer connected through WebSockets.

This project is experimental and currently intended for learning, prototyping, and exploring how a NiceGUI-style programming model could work in modern C++.

## Example

```cpp
import UI;

auto main() -> int
{
	auto app = ui::App{};

	auto counter = 0;

	app.RegisterPage("/", [&]( ui::PageBuilder& ui ){
		auto& label1 = ui.Label( "Test" );

		ui.Container( [&]{
			ui.Label( "Test2" );
		} );

		ui.Container( [&]{
			ui.Button( "Click me!", [&]{
				counter++;

				// label1.text is a custom property type with getters and
				// setters, so setting it updates the browser immediately.
				label1.text = "Clicked times: " + std::to_string( counter );
			} );
		} );
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
    -> browser sends current path

Server receives path
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
* Basic DOM element creation
* Basic text updates
* Button click events from browser to server
* Reactive-style property updates
* Static browser assets served from the `www` directory

## Current Architecture

The application is centered around `ui::App`.

`ui::App` is responsible for:

* loading the Drogon configuration
* registering pages
* starting the server
* coordinating page creation

A registered page looks like this:

```cpp
app.RegisterPage("/", []( ui::PageBuilder& ui ){
	ui.Label( "Hello" );

	ui.Button( "Click me", []{
		// server-side callback
	} );
} );
```

The browser initially receives a template document. The actual UI is built after the WebSocket connection is established.

## Browser Protocol

CppWebUI communicates with the browser using JSON messages over WebSockets.

Example browser-to-server message:

```json
{
	"op": "button_clicked",
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
	"op": "update_text",
	"id": "label-uuid",
	"text": "Clicked times: 1"
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
* sending click events from browser to server
* updating server-side UI state
* pushing text updates back to the browser

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
