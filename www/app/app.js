
const wsProtocol = window.location.protocol === "https:" ? "wss:" : "ws:";
const wsUrl = `${wsProtocol}//${window.location.host}/ws`;

const socket = new WebSocket(wsUrl);


socket.addEventListener("open", () => {
	socket.send(JSON.stringify({
		op: "connect",
		route_path: window.location.pathname,
		query: window.location.search,
		hash: window.location.hash
	}));
});


socket.addEventListener("message", (event) => {
	let message;
	try {
		message = JSON.parse(event.data);
	}
	catch (error) {
		console.error("Invalid JSON from server:", event.data, error);
		return;
	}

	switch (message.op) {
		case "create_element":
			CreateElement(message.parent_id, message.tag, message.id);
			break;

		case "delete_element":
			DeleteElement(message.id);
			break;

		case "set_tag":
			SetTag(message.id, message.tag);
			break;

		case "set_attribute":
			SetAttribute(message.id, message.attribute, message.attribute_value);
			break;

		case "set_text":
			SetText(message.id, message.text);
			break;

		case "set_modal_open":
			SetModalOpen(message.id, message.open);

		case "set_on_click":
			SetOnClick(message.id);
			break;

		case "set_on_change":
			SetOnChange(message.id);
			break;

		case "set_on_submit":
			SetOnSubmit(message.id);
			break;

		default:
			console.warn("Unknown message op:", message.op, message);
			break;
	}
});


function CreateElement(parentId, tag, id)
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


function DeleteElement(id)
{
	document.getElementById(id)?.remove();
}


function SetTag(id, tag)
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


function SetAttribute(id, attribute, value)
{
	document.getElementById(id).setAttribute(attribute, value);
}


function SetText(id, text)
{
	document.getElementById(id).textContent = text;
}


function SetModalOpen(id, open)
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


function AddClass(id, className)
{
	document.getElementById(id).classList.add(className);
}


document.addEventListener("click", (event) => {
	const element = event.target.closest("[data-ui-on-click]");

	if (!element) {
		return;
	}

	socket.send(JSON.stringify({
		op: "on_click",
		id: element.id
	}));
});


document.addEventListener("change", (event) => {
	const element = event.target.closest("[data-ui-on-change]");

	if (!element) {
		return;
	}

	socket.send(JSON.stringify({
		op: "on_change",
		id: element.id,
		value: GetElementValue(element)
	}));
});


document.addEventListener("submit", (event) => {
	const element = event.target.closest("[data-ui-on-submit]");

	if (!element) {
		return;
	}

	event.preventDefault();

	socket.send(JSON.stringify({
		op: "on_submit",
		id: element.id
	}));
});


function GetElementValue(element)
{
	if (element.type === "checkbox") {
		return element.checked;
	}

	return element.value;
}


function SetOnClick(id)
{
	const element = document.getElementById(id);

	if (element === null)
	{
		console.error("Element not found:", id);
		return;
	}

	element.dataset.uiOnClick = "true";
}


function SetOnChange(id)
{
	const element = document.getElementById(id);

	if (element === null)
	{
		console.error("Element not found:", id);
		return;
	}

	element.dataset.uiOnChange = "true";
}


function SetOnSubmit(id)
{
	const element = document.getElementById(id);

	if (element === null)
	{
		console.error("Element not found:", id);
		return;
	}

	element.dataset.uiOnSubmit = "true";
}