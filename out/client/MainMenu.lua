-- Compiled with roblox-ts v2.2.0
local TS = require(game:GetService("ReplicatedStorage"):WaitForChild("rbxts_include"):WaitForChild("RuntimeLib"))
local _Util = TS.import(script, game:GetService("ReplicatedStorage"), "TS", "Util")
local GetTaggedUI = _Util.GetTaggedUI
local GetValue = _Util.GetValue
local UIPanelWithFader = TS.import(script, script.Parent, "UIPanel").UIPanelWithFader
local MainMenuUI
do
	local super = UIPanelWithFader
	MainMenuUI = setmetatable({}, {
		__tostring = function()
			return "MainMenuUI"
		end,
		__index = super,
	})
	MainMenuUI.__index = MainMenuUI
	function MainMenuUI.new(...)
		local self = setmetatable({}, MainMenuUI)
		return self:constructor(...) or self
	end
	function MainMenuUI:constructor(uimng)
		super.constructor(self, uimng)
		self.parent = GetTaggedUI("MainMenuUI")
		if not self.parent then
			warn("[Main Menu UI] Could not find parent tagged MainMenuUI")
		else
			self.RootUI = GetValue("RootUI", self.parent)
			if not self.RootUI then
				warn("[Main Menu] Can't find Root UI")
				return nil
			end
			self:InitializePanel(self.parent)
			self:SetEnable(true)
		end
	end
end
return {
	MainMenuUI = MainMenuUI,
}
