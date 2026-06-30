
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
	const message = JSON.parse(event.data);

	if( message.op === "create_element" ) CreateElement(message.parent_id, message.tag, message.id);
	if(message.op === "set_text") SetText(message.id, message.text);
	if(message.op === "set_on_click") SetOnClick(message.id);
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

function SetText(id, text)
{
	document.getElementById(id).textContent = text;
}

function AddClass(id, className)
{
	document.getElementById(id).classList.add(className);
}

function RemoveElement(id)
{
	document.getElementById(id)?.remove();
}

function SetOnClick(id)
{
	BindButton(id);
}

function BindButton(id)
{
	const button = document.getElementById(id);

	if (button === null)
	{
		console.error("Button not found:", id);
		return;
	}

	button.addEventListener("click", () =>
	{
		socket.send(JSON.stringify({
			op: "button_clicked",
			id: id
		}));
	});
}
