TextStyler = Object:extend() 

function TextStyler:new()
	self.defaultFont = love.graphics.newFont("assets/fonts/Junicode-Regular.ttf", 24)
	self.boldFont = love.graphics.newFont("assets/fonts/Junicode-Bold.ttf", 24)
	self.italicFont = love.graphics.newFont("assets/fonts/Junicode-Italic.ttf", 24)
	self.boldItalicFont = love.graphics.newFont("assets/fonts/Junicode-BoldItalic.ttf", 24)
	self.currentStyle = 1
	self.maxStyle = 4
	self.styleTable = 
	{
		self.default,
		self.bold,
		self.italic,
		self.boldItalic
	}
end

function TextStyler:advanceStyle()
	self.currentStyle = (self.currentStyle % 4) + 1
end

function TextStyler:current()
	local func = self.styleTable[self.currentStyle]

	if (func) then
		func(self)
	else
		print("didn't find a function "..self.currentStyle)
	end
end

function TextStyler:default()
	love.graphics.setColor(1, 1, 1, 1) -- default color
	love.graphics.setFont(self.defaultFont) -- default font and size
	print("setting font to default")
end

function TextStyler:bold()
	love.graphics.setColor(1, 1, 1, 1) -- default color
	love.graphics.setFont(self.boldFont)
	print("setting font to bold")
end

function TextStyler:italic()
	love.graphics.setColor(1, 1, 1, 1) -- default color
	love.graphics.setFont(self.italicFont)
	print("setting font to italic")
end

function TextStyler:boldItalic()
	love.graphics.setColor(1, 1, 1, 1) -- default color
	love.graphics.setFont(self.boldItalicFont)
	print("setting font to bold italic")
end
