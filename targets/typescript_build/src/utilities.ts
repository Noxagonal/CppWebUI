
export function stringToBoolean(value: string): boolean
{
	if (value.toLowerCase() === "true") return true;
	if (value.toLowerCase() === "1") return true;
	return false;
}
