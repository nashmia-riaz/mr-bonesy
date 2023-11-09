-- Compiled with roblox-ts v2.2.0
local TS = require(game:GetService("ReplicatedStorage"):WaitForChild("rbxts_include"):WaitForChild("RuntimeLib"))
local EventManager = TS.import(script, game:GetService("ReplicatedStorage"), "TS", "Util").EventManager
local _Services = TS.import(script, game:GetService("ReplicatedStorage"), "TS", "Services")
local Players = _Services.Players
local RunService = _Services.RunService
local MainMenuUI = TS.import(script, script.Parent, "MainMenu").MainMenuUI
local UIManager
do
	UIManager = setmetatable({}, {
		__tostring = function()
			return "UIManager"
		end,
	})
	UIManager.__index = UIManager
	function UIManager.new(...)
		local self = setmetatable({}, UIManager)
		return self:constructor(...) or self
	end
	function UIManager:constructor(gamemanager)
		self.isInitialized = false
		self.OnUIInitEvent = EventManager.new()
		self.gameManager = gamemanager
		self:WaitForPlayerGUI()
		self.mainMenu = MainMenuUI.new(self)
	end
	function UIManager:ExecuteOnInit(onInit)
		if self.isInitialized then
			onInit()
		else
			self.OnUIInitEvent:Subscribe(onInit)
		end
	end
	function UIManager:WaitForPlayerGUI()
		local playerGUI = Players.LocalPlayer:WaitForChild("PlayerGui")
		local totalUIElements = #game:GetService("StarterGui"):GetDescendants()
		--wait for all starter gui elements to be copied over to player side
		while #playerGUI:GetDescendants() < totalUIElements do
			RunService.Heartbeat:Wait()
		end
		self.isInitialized = true
		self.OnUIInitEvent:Invoke(true)
		print("[UI Manager] Initialized player GUI with " .. (tostring(totalUIElements) .. " elements"))
	end
end
return {
	UIManager = UIManager,
}
