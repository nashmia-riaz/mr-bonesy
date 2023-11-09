-- Compiled with roblox-ts v2.2.0
local TS = require(game:GetService("ReplicatedStorage"):WaitForChild("rbxts_include"):WaitForChild("RuntimeLib"))
local Time = TS.import(script, game:GetService("ReplicatedStorage"), "TS", "Time").Time
local UIManager = TS.import(script, script.Parent, "UIManager").UIManager
local ClientGameManager
do
	ClientGameManager = setmetatable({}, {
		__tostring = function()
			return "ClientGameManager"
		end,
	})
	ClientGameManager.__index = ClientGameManager
	function ClientGameManager.new(...)
		local self = setmetatable({}, ClientGameManager)
		return self:constructor(...) or self
	end
	function ClientGameManager:constructor()
		self.timeManager = Time.new()
		self.uiManager = UIManager.new(self)
	end
	function ClientGameManager:Run()
	end
end
return {
	ClientGameManager = ClientGameManager,
}
