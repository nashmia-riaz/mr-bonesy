-- Compiled with roblox-ts v2.2.0
local TS = require(game:GetService("ReplicatedStorage"):WaitForChild("rbxts_include"):WaitForChild("RuntimeLib"))
local TweenService = TS.import(script, game:GetService("ReplicatedStorage"), "TS", "Services").TweenService
local UIPanelBasic
do
	UIPanelBasic = setmetatable({}, {
		__tostring = function()
			return "UIPanelBasic"
		end,
	})
	UIPanelBasic.__index = UIPanelBasic
	function UIPanelBasic.new(...)
		local self = setmetatable({}, UIPanelBasic)
		return self:constructor(...) or self
	end
	function UIPanelBasic:constructor(uimng)
		self.UIManager = uimng
	end
	function UIPanelBasic:SetEnable(enable)
		if not self.RootUI then
			warn("[UI Panel] No Root UI found")
			return nil
		end
		local _exp = self.RootUI
		_exp.Visible = enable
		self.RootUI.Active = _exp.Visible
	end
end
local UIPanelWithFader
do
	local super = UIPanelBasic
	UIPanelWithFader = setmetatable({}, {
		__tostring = function()
			return "UIPanelWithFader"
		end,
		__index = super,
	})
	UIPanelWithFader.__index = UIPanelWithFader
	function UIPanelWithFader.new(...)
		local self = setmetatable({}, UIPanelWithFader)
		return self:constructor(...) or self
	end
	function UIPanelWithFader:constructor(uiMng)
		super.constructor(self, uiMng)
		self.currentState = false
	end
	function UIPanelWithFader:SetEnable(enable)
		if enable and not self.currentState then
			local _exp = self.RootUI
			_exp.Visible = enable
			self.RootUI.Active = _exp.Visible
			local _result = self.fadeIn
			if _result ~= nil then
				_result:Play()
			end
		elseif not enable and self.currentState then
			local _result = self.fadeOut
			if _result ~= nil then
				_result:Play()
			end
		end
		self.currentState = enable
	end
	function UIPanelWithFader:InitializePanel(panel)
		self.canvasGroup = panel
		if not self.canvasGroup then
			warn("[UI Panel] No canvas group found")
			return nil
		end
		self.fadeIn = TweenService:Create(self.canvasGroup, TweenInfo.new(0.5, Enum.EasingStyle.Linear, Enum.EasingDirection.InOut, 0, false), {
			GroupTransparency = 0,
		})
		self.fadeOut = TweenService:Create(self.canvasGroup, TweenInfo.new(0.5, Enum.EasingStyle.Linear, Enum.EasingDirection.InOut, 0, false), {
			GroupTransparency = 1,
		})
		self.fadeOut.Completed:Connect(function()
			local _exp = self.RootUI
			_exp.Visible = false
			self.RootUI.Active = _exp.Visible
		end)
		print("[UI Panel] Initialized")
	end
end
return {
	UIPanelBasic = UIPanelBasic,
	UIPanelWithFader = UIPanelWithFader,
}
