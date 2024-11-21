TextStyler = Object:extend() 

function TextStyler:new()
	self.defaultFont = love.graphics.newFont("assets/fonts/Junicode-Regular.ttf", 24)
	self.boldFont = love.graphics.newFont("assets/fonts/Junicode-Bold.ttf", 24)
	self.italicFont = love.graphics.newFont("assets/fonts/Junicode-Italic.ttf", 24)
	self.boldItalicFont = love.graphics.newFont("assets/fonts/Junicode-BoldItalic.ttf", 24)
	self.currentStyle = "default"
	self.maxStyle = 4
	self.styleTable = 
	{
		default = self.default,
		bold = self.bold,
		italic = self.italic,
		boldItalic = self.boldItalic
	}
	self.heightTable = 
	{
		default = self.defaultFont:getHeight(" ")
	}
end

function TextStyler:setStyle(style)
	self.currentStyle = style
end

function TextStyler:getHeight(style)
	return self.heightTable[style] or 0 
end

function TextStyler:drawStyle()
	local func = self.styleTable[self.currentStyle]

	if (func) then
		func(self)
	else
		--print("didn't find a style for "..self.currentStyle)
	end
end

function TextStyler:default()
	love.graphics.setColor(1, 1, 1, 1) -- default color
	love.graphics.setFont(self.defaultFont) -- default font and size
	--print("setting font to default")
end

function TextStyler:bold()
	love.graphics.setColor(1, 1, 1, 1) -- default color
	love.graphics.setFont(self.boldFont)
	--print("setting font to bold")
end

function TextStyler:italic()
	love.graphics.setColor(1, 1, 1, 1) -- default color
	love.graphics.setFont(self.italicFont)
	--print("setting font to italic")
end

function TextStyler:boldItalic()
	love.graphics.setColor(1, 1, 1, 1) -- default color
	love.graphics.setFont(self.boldItalicFont)
	--print("setting font to bold italic")
end
