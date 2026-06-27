
const socket = new WebSocket("ws://localhost:8080/ws");

socket.addEventListener("open", () => {
	console.log("WebSocket connected");
	socket.send("Hello from browser");
});

socket.addEventListener("message", (event) => {
	console.log("Message from server:", event.data);
});

socket.addEventListener("close", () => {
	console.log("WebSocket closed");
});

socket.addEventListener("error", (error) => {
	console.error("WebSocket error:", error);
});

function ButtonPressed()
{
	if(socket.readyState === WebSocket.OPEN)
	{
		socket.send("Button was clicked");
	}
	else
	{
		console.log("WebSocket is not open");
	}
}

const button = document.getElementById("TestButton");
button.onclick = ButtonPressed;
