import { Players } from "./Services";

export class EventManager {
	constructor() {}
	listeners: ((args: unknown) => void)[] = [];

	Subscribe(listener: () => void) {
		this.listeners.push(listener);
	}

	Invoke(args: unknown) {
		this.listeners.forEach((listener) => {
			listener(args);
		});
	}

	Unsubscribe(listener: () => void) {
		const listernerFound = this.listeners.remove(this.listeners.indexOf(listener));
		if (!listernerFound) warn("[Event manager] Could not find the listener");
	}
}

export class Timer {
	timer = 0;
	timeLimit = 0;
	constructor(timeLimit: number) {
		this.timeLimit = timeLimit;
	}

	Update() {}
}

export function GetTaggedUI(tag: string): Instance | undefined {
	let instance: Instance | undefined;
	const PlayerGui = Players.LocalPlayer.WaitForChild("PlayerGui");
	PlayerGui.GetDescendants().forEach((descendant) => {
		if (descendant.HasTag(tag)) {
			instance = descendant as Instance;
			return instance;
		}
	});
	return instance;
}

export function GetValue<T>(tag: string, parent: Instance): T | undefined {
	const descendants = parent.GetDescendants();
	for (let i = 0; i < descendants.size(); i++) {
		const descendant = descendants[i];
		if (descendant.IsA("ObjectValue")) {
			if (descendant.Name === tag) return descendant.Value as T;
		}
	}

	return undefined;
}
