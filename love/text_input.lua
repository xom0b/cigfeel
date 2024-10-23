TextInput = Object:extend()

function TextInput:new(rect)
	self.rect = rect
	self.text = ""
	self.textRender = love.graphics.newText(love.graphics.getFont(), "")
end