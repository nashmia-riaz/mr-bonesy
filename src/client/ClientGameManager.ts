import { Time } from "shared/Time";
import { UIManager } from "./UIManager";

export class ClientGameManager {
	uiManager!: UIManager;
	timeManager!: Time;

	constructor() {
		this.timeManager = new Time();
		this.uiManager = new UIManager(this);
	}
	Run() {}
}
