import { GetTaggedUI, GetValue } from "shared/Util";
import { UIManager } from "./UIManager";
import { UIPanelBasic, UIPanelWithFader } from "./UIPanel";

export class MainMenuUI extends UIPanelWithFader {
	parent!: Instance;
	constructor(uimng: UIManager) {
		super(uimng);
		this.parent = GetTaggedUI("MainMenuUI")!;
		if (!this.parent) warn(`[Main Menu UI] Could not find parent tagged MainMenuUI`);
		else {
			this.RootUI = GetValue<Frame>("RootUI", this.parent);
			if (!this.RootUI) {
				warn(`[Main Menu] Can't find Root UI`);
				return;
			}

			this.InitializePanel(this.parent as CanvasGroup);
			this.SetEnable(true);
		}
	}
}
