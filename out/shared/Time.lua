-- Compiled with roblox-ts v2.2.0
local TS = require(game:GetService("ReplicatedStorage"):WaitForChild("rbxts_include"):WaitForChild("RuntimeLib"))
local EventManager = TS.import(script, game:GetService("ReplicatedStorage"), "TS", "Util").EventManager
local RunService = TS.import(script, game:GetService("ReplicatedStorage"), "TS", "Services").RunService
local Time
do
	Time = setmetatable({}, {
		__tostring = function()
			return "Time"
		end,
	})
	Time.__index = Time
	function Time.new(...)
		local self = setmetatable({}, Time)
		return self:constructor(...) or self
	end
	function Time:constructor()
		self.prevFrameTime = 0
		self.currentFrameTime = 0
		self.overallTime = 0
		self.DeltaTime = EventManager.new()
		self:Init()
	end
	function Time:Init()
		RunService.Heartbeat:Connect(function(dt)
			self.prevFrameTime = self.currentFrameTime
			self.overallTime += dt
			self.currentFrameTime = self.overallTime
			self.DeltaTime:Invoke(self.currentFrameTime - self.prevFrameTime)
		end)
	end
end
return {
	Time = Time,
}
