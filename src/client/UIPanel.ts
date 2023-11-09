import { TweenService } from "shared/Services";
import { UIManager } from "./UIManager";

export class UIPanelBasic {
	UIManager!: UIManager;

	RootUI: Frame | undefined;

	constructor(uimng: UIManager) {
		this.UIManager = uimng;
	}

	SetEnable(enable: boolean) {
		if (!this.RootUI) {
			warn(`[UI Panel] No Root UI found`);
			return;
		}
		this.RootUI.Active = this.RootUI.Visible = enable;
	}
}

export class UIPanelWithFader extends UIPanelBasic {
	canvasGroup: CanvasGroup | undefined;

	fadeIn: Tween | undefined;
	fadeOut: Tween | undefined;

	currentState = false;

	constructor(uiMng: UIManager) {
		super(uiMng);
	}

	override SetEnable(enable: boolean): void {
		if (enable && !this.currentState) {
			this.RootUI!.Active = this.RootUI!.Visible = enable;
			this.fadeIn?.Play();
		} else if (!enable && this.currentState) {
			this.fadeOut?.Play();
		}
		this.currentState = enable;
	}

	InitializePanel(panel: CanvasGroup) {
		this.canvasGroup = panel;
		if (!this.canvasGroup) {
			warn(`[UI Panel] No canvas group found`);
			return;
		}

		this.fadeIn = TweenService.Create(
			this.canvasGroup,
			new TweenInfo(0.5, Enum.EasingStyle.Linear, Enum.EasingDirection.InOut, 0, false),
			{
				GroupTransparency: 0,
			},
		);

		this.fadeOut = TweenService.Create(
			this.canvasGroup,
			new TweenInfo(0.5, Enum.EasingStyle.Linear, Enum.EasingDirection.InOut, 0, false),
			{
				GroupTransparency: 1,
			},
		);
		this.fadeOut.Completed.Connect(() => {
			this.RootUI!.Active = this.RootUI!.Visible = false;
		});
		print(`[UI Panel] Initialized`);
	}
}
