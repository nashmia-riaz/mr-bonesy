-- Compiled with roblox-ts v2.2.0
local TS = require(game:GetService("ReplicatedStorage"):WaitForChild("rbxts_include"):WaitForChild("RuntimeLib"))
local Players = TS.import(script, game:GetService("ReplicatedStorage"), "TS", "Services").Players
local EventManager
do
	EventManager = setmetatable({}, {
		__tostring = function()
			return "EventManager"
		end,
	})
	EventManager.__index = EventManager
	function EventManager.new(...)
		local self = setmetatable({}, EventManager)
		return self:constructor(...) or self
	end
	function EventManager:constructor()
		self.listeners = {}
	end
	function EventManager:Subscribe(listener)
		local _listeners = self.listeners
		local _listener = listener
		table.insert(_listeners, _listener)
	end
	function EventManager:Invoke(args)
		local _listeners = self.listeners
		local _arg0 = function(listener)
			listener(args)
		end
		for _k, _v in _listeners do
			_arg0(_v, _k - 1, _listeners)
		end
	end
	function EventManager:Unsubscribe(listener)
		local _listeners = self.listeners
		local _listeners_1 = self.listeners
		local _listener = listener
		local _arg0 = (table.find(_listeners_1, _listener) or 0) - 1
		local listernerFound = table.remove(_listeners, _arg0 + 1)
		if not listernerFound then
			warn("[Event manager] Could not find the listener")
		end
	end
end
local Timer
do
	Timer = setmetatable({}, {
		__tostring = function()
			return "Timer"
		end,
	})
	Timer.__index = Timer
	function Timer.new(...)
		local self = setmetatable({}, Timer)
		return self:constructor(...) or self
	end
	function Timer:constructor(timeLimit)
		self.timer = 0
		self.timeLimit = 0
		self.timeLimit = timeLimit
	end
	function Timer:Update()
	end
end
local function GetTaggedUI(tag)
	local instance
	local PlayerGui = Players.LocalPlayer:WaitForChild("PlayerGui")
	local _exp = PlayerGui:GetDescendants()
	local _arg0 = function(descendant)
		if descendant:HasTag(tag) then
			instance = descendant
			return instance
		end
	end
	for _k, _v in _exp do
		_arg0(_v, _k - 1, _exp)
	end
	return instance
end
local function GetValue(tag, parent)
	local descendants = parent:GetDescendants()
	do
		local i = 0
		local _shouldIncrement = false
		while true do
			if _shouldIncrement then
				i += 1
			else
				_shouldIncrement = true
			end
			if not (i < #descendants) then
				break
			end
			local descendant = descendants[i + 1]
			if descendant:IsA("ObjectValue") then
				if descendant.Name == tag then
					return descendant.Value
				end
			end
		end
	end
	return nil
end
return {
	GetTaggedUI = GetTaggedUI,
	GetValue = GetValue,
	EventManager = EventManager,
	Timer = Timer,
}
