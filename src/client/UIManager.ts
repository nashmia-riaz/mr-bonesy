import { EventManager } from "shared/Util";
import { ClientGameManager } from "./ClientGameManager";
import { Players, RunService } from "shared/Services";
import { MainMenuUI } from "./MainMenu";

export class UIManager {
	gameManager!: ClientGameManager;

	isInitialized = false;

	OnUIInitEvent: EventManager = new EventManager();

	mainMenu!: MainMenuUI;
	ExecuteOnInit(onInit: () => void) {
		if (this.isInitialized) {
			onInit();
		} else {
			this.OnUIInitEvent.Subscribe(onInit);
		}
	}

	constructor(gamemanager: ClientGameManager) {
		this.gameManager = gamemanager;
		this.WaitForPlayerGUI();

		this.mainMenu = new MainMenuUI(this);
	}

	WaitForPlayerGUI() {
		const playerGUI = Players.LocalPlayer.WaitForChild("PlayerGui");
		const totalUIElements = game.GetService("StarterGui").GetDescendants().size();

		//wait for all starter gui elements to be copied over to player side
		while (playerGUI.GetDescendants().size() < totalUIElements) RunService.Heartbeat.Wait();

		this.isInitialized = true;
		this.OnUIInitEvent.Invoke(true);
		print(`[UI Manager] Initialized player GUI with ${totalUIElements} elements`);
	}
}
