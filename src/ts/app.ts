
const wsProtocol = window.location.protocol === "https:" ? "wss:" : "ws:";
const wsUrl = `${wsProtocol}//${window.location.host}/ws`;

const socket = new WebSocket(wsUrl);


type ReceiveServerMessage =
	| { op: "create_element"; parent_id: string; tag: string; id: string }
	| { op: "delete_element"; id: string }
	| { op: "set_tag"; id: string; tag: string } // Deprecated: Removing this.
	| { op: "set_attribute"; id: string; attribute: string; attribute_value: string }
	| { op: "remove_attribute"; id: string; attribute: string; }
	| { op: "add_class"; id: string; class_name: string }
	| { op: "remove_class"; id: string; class_name: string }
	| { op: "set_text"; id: string; text: string }
	| { op: "set_value"; id: string; value: string }
	| { op: "set_modal_open"; id: string; open: boolean }
	| { op: "set_on_click"; id: string }
	| { op: "set_on_change"; id: string }
	| { op: "set_on_submit"; id: string };

type SendServerMessage =
	| { op: "connect"; route_path: string; query: string; hash: string }
	| { op: "on_click"; id: string }
	| { op: "on_change"; id: string, value: string | boolean }
	| { op: "on_submit"; id: string };


function parseServerMessage(event: MessageEvent): ReceiveServerMessage
{
	if (typeof event.data !== "string") {
		throw new Error("Expected text WebSocket message");
	}

	return JSON.parse(event.data) as ReceiveServerMessage;
}


function sendToServer(message: SendServerMessage): void
{
	if (socket.readyState !== WebSocket.OPEN) {
		console.warn("WebSocket is not open. Message not sent: ", message);
		return;
	}

	socket.send(JSON.stringify(message));
}


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


function createElement(
	parentId: string,
	tag: string,
	id: string
): void
{
	const parent = document.getElementById(parentId);

	if (parent === null)
	{
		console.error("Parent not found:", parentId);
		return;
	}

	const element = document.createElement(tag);
	element.id = id;

	parent.appendChild(element);
}


function deleteElement(id: string): void
{
	document.getElementById(id)?.remove();
}


// Deprecated: This function will be deleted.
function setTag(
	id: string,
	tag: string
): void
{
	const oldElement = document.getElementById(id);
	if (!oldElement) {
		console.warn("SetTag failed, element not found:", id);
		return;
	}

	const newElement = document.createElement(tag);

	// Copy attributes, including id.
	for (const attribute of oldElement.attributes) {
		newElement.setAttribute(attribute.name, attribute.value);
	}

	// Move child nodes over.
	while (oldElement.firstChild) {
		newElement.appendChild(oldElement.firstChild);
	}

	oldElement.replaceWith(newElement);
}


function setAttribute(
	id: string,
	attribute: string,
	value: string
): void
{
	if (attribute.toLowerCase().startsWith("on")) {
		console.warn("Blocked event-handler attribute:", attribute);
		return;
	}

	document.getElementById(id)?.setAttribute(attribute, value);
}


function removeAttribute(
	id: string,
	attribute: string
): void
{
	document.getElementById(id)?.removeAttribute(attribute);
}


function addClass(
	id: string,
	className: string
): void
{
	document.getElementById(id)?.classList.add(className);
}


function removeClass(
	id: string,
	className: string
): void
{
	document.getElementById(id)?.classList.remove(className);
}


function setText(
	id: string,
	text: string
): void
{
	const element = document.getElementById(id);
	if (element !== null) element.textContent = text;
}


function stringToBoolean(value: string): boolean
{
	if (value.toLowerCase() === "true") return true;
	if (value.toLowerCase() === "1") return true;
	return false;
}


function setValue(
	id: string,
	value: string
): void
{
	const element = document.getElementById(id);

	if (element === null) {
		console.warn("setValue failed, element not found: ", id);
		return;
	}

	if (element instanceof HTMLInputElement) {
		if (element.type === "checkbox") {
			element.checked = stringToBoolean(value);
			return;
		}
		element.value = value;
		return;
	}

	if (element instanceof HTMLTextAreaElement) {
		element.value = value;
		return;
	}

	if (element instanceof HTMLSelectElement) {
		element.value = value;
		return;
	}

	console.warn("setValue called on unsupported element: ", element, " | While trying to assing value: ", value);
}


function setModalOpen(
	id: string,
	open: boolean
): void
{
	const element = document.getElementById(id);

	if (!element) {
		console.warn("SetModalOpen failed, element not found:", id);
		return;
	}

	if (!(element instanceof HTMLDialogElement)) {
		console.warn("SetModalOpen failed, element is not a dialog:", id);
		return;
	}

	if (open) {
		if (!element.open) {
			element.showModal();
		}
	}
	else {
		if (element.open) {
			element.close();
		}
	}
}


document.addEventListener("click", (event) => {
	const target = event.target;
	if (!(target instanceof Element)) return;

	const element = target.closest("[data-ui-on-click]");
	if (!element) return;

	sendToServer({
		op: "on_click",
		id: element.id
	});
});


document.addEventListener(
	"change",
	(event) => {
	const target = event.target;
	if (!(target instanceof Element)) return;

	const element = target.closest("[data-ui-on-change]");
	if (!element) return;

	const elementValue = getElementValue(element);
	if (elementValue === null)
	{
		console.warn("Element has no value");
		return;
	}

	sendToServer({
		op: "on_change",
		id: element.id,
		value: elementValue
	});
});


document.addEventListener(
	"submit",
	(event) => {
	const target = event.target;
	if (!(target instanceof Element)) return;

	const element = target.closest("[data-ui-on-submit]");
	if (!element) return;

	event.preventDefault();

	sendToServer({
		op: "on_submit",
		id: element.id
	});
});


function getElementValue(element: Element): null | string | boolean
{
	if (element instanceof HTMLInputElement) {
		if (element.type === "checkbox") return element.checked;

		return element.value;
	}

	if (element instanceof HTMLTextAreaElement) {
		return element.value;
	}

	if (element instanceof HTMLSelectElement) {
		return element.value;
	}

	console.warn("getElementValue called on unsupported element: ", element);
	return null;
}


function setOnClick(id: string): void
{
	const element = document.getElementById(id);

	if (element === null)
	{
		console.error("Element not found:", id);
		return;
	}

	element.dataset.uiOnClick = "true";
}


function setOnChange(id: string): void
{
	const element = document.getElementById(id);

	if (element === null)
	{
		console.error("Element not found:", id);
		return;
	}

	element.dataset.uiOnChange = "true";
}


function setOnSubmit(id: string): void
{
	const element = document.getElementById(id);

	if (element === null)
	{
		console.error("Element not found:", id);
		return;
	}

	element.dataset.uiOnSubmit = "true";
}
