import { EventManager } from "shared/Util";
import { RunService } from "./Services";

export class Time {
	prevFrameTime = 0;
	currentFrameTime = 0;
	overallTime = 0;

	DeltaTime: EventManager = new EventManager();

	constructor() {
		this.Init();
	}

	Init() {
		RunService.Heartbeat.Connect((dt) => {
			this.prevFrameTime = this.currentFrameTime;
			this.overallTime += dt;
			this.currentFrameTime = this.overallTime;

			this.DeltaTime.Invoke(this.currentFrameTime - this.prevFrameTime);
		});
	}
}
