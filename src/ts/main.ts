
import { ReceiveServerMessage } from "./protocol.js"
import { socket, parseServerMessage, sendToServer } from "./websocket.js";
import { registerBrowserEventHandlers } from "./events.js";
import {
	addClass,
	createElement,
	deleteElement,
	removeAttribute,
	removeClass,
	setAttribute,
	setModalOpen,
	setOnChange,
	setOnClick,
	setOnSubmit,
	setTag,
	setText,
	setValue,
} from "./dom-ops.js";


registerBrowserEventHandlers();


socket.addEventListener(
	"open",
	() => {
	sendToServer({
		op: "connect",
		route_path: window.location.pathname,
		query: window.location.search,
		hash: window.location.hash
	});
});


socket.addEventListener(
	"message",
	(event) => {
	let message: ReceiveServerMessage;
	try {
		message = parseServerMessage(event);
	}
	catch (error) {
		console.error("Invalid JSON from server:", event.data, error);
		return;
	}

	switch (message.op) {
		case "create_element":
			createElement(message.parent_id, message.tag, message.id);
			break;

		case "delete_element":
			deleteElement(message.id);
			break;

		case "set_tag": // Deprecated: Going to be removed.
			setTag(message.id, message.tag);
			break;

		case "set_attribute":
			setAttribute(message.id, message.attribute, message.attribute_value);
			break;

		case "remove_attribute":
			removeAttribute(message.id, message.attribute);
			break;

		case "add_class":
			addClass(message.id, message.class_name);
			break;

		case "remove_class":
			removeClass(message.id, message.class_name);
			break;

		case "set_text":
			setText(message.id, message.text);
			break;

		case "set_value":
			setValue(message.id, message.value);
			break;

		case "set_modal_open":
			setModalOpen(message.id, message.open);
			break;

		case "set_on_click":
			setOnClick(message.id);
			break;

		case "set_on_change":
			setOnChange(message.id);
			break;

		case "set_on_submit":
			setOnSubmit(message.id);
			break;

		default:
			console.warn("Unknown message:", message);
			break;
	}
});
