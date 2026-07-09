
import { stringToBoolean } from "./utilities.js";


export function createElement(
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


export function deleteElement(id: string): void
{
	document.getElementById(id)?.remove();
}


// Deprecated: This function will be deleted.
export function setTag(
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


export function setAttribute(
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


export function removeAttribute(
	id: string,
	attribute: string
): void
{
	document.getElementById(id)?.removeAttribute(attribute);
}


export function addClass(
	id: string,
	className: string
): void
{
	document.getElementById(id)?.classList.add(className);
}


export function removeClass(
	id: string,
	className: string
): void
{
	document.getElementById(id)?.classList.remove(className);
}


export function setText(
	id: string,
	text: string
): void
{
	const element = document.getElementById(id);
	if (element !== null) element.textContent = text;
}


export function setValue(
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


export function setModalOpen(
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


export function getElementValue(element: Element): null | string | boolean
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


export function setOnClick(id: string): void
{
	const element = document.getElementById(id);

	if (element === null)
	{
		console.error("Element not found:", id);
		return;
	}

	element.dataset.uiOnClick = "true";
}


export function setOnChange(id: string): void
{
	const element = document.getElementById(id);

	if (element === null)
	{
		console.error("Element not found:", id);
		return;
	}

	element.dataset.uiOnChange = "true";
}


export function setOnSubmit(id: string): void
{
	const element = document.getElementById(id);

	if (element === null)
	{
		console.error("Element not found:", id);
		return;
	}

	element.dataset.uiOnSubmit = "true";
}
