TextRect = Object:extend()

function TextRect:new(rect)
	self.rect = rect
	self.text = ""
	self.textRender = love.graphics.newText(love.graphics.getFont(), "")
	self.lines = {}
	self.wiggleStrength = 5
	self.wiggleSpeed = 5
	self.wiggleDivider = 8
	self.wiggleOffset = math.pi / self.wiggleDivider
end

function TextRect:setText(text)
	self.text = text
end

function TextRect:appendText(text)
	self.text = self.text..text
end

function TextRect:appendNewLine()
	self.text = self.text.."\n"
end

function TextRect:removeText()
	-- get the byte offset to the last UTF-8 character in the string.
    local byteoffset = utf8.offset(self.text, -1)

    if byteoffset then
        -- remove the last UTF-8 character.
        -- string.sub operates on bytes rather than UTF-8 characters, so we couldn't do string.sub(text, 1, -2).
        self.text = string.sub(self.text, 1, byteoffset - 1)
    end
end

function TextRect:adjustDivider(adjustment)
	self.wiggleDivider = self.wiggleDivider + adjustment
	self.wiggleOffset = math.pi / self.wiggleDivider
end

function TextRect:keypressed(key)
	if key == "backspace" then
        self:removeText()
    elseif key == "return" then
        self:appendNewLine()
    end

    if key == "up" then
    	self:adjustDivider(1)
	elseif key == "down" then
		self:adjustDivider(-1)
	end
end

function TextRect:update(dt)
end

function TextRect:draw()
	-- TODO: cache styles and blocks
	
	self.rect:draw()

	love.graphics.push()
	love.graphics.applyTransform(self.rect.transform)
	love.graphics.setColor(1, 1, 1, 1)

	-- grab styles
	local styles = {}
	for style in string.gmatch(self.text, "%b{}") do -- match braces
		local style = string.gsub(style, '%W', '') -- remove the braces (remove non-alphanumeric chars)
		table.insert(styles, style)
	end

	-- grab style blocks
	local blocks = {}
	for wordIndex in string.gmatch(self.text, "%b{}()") do
		local bracesIndex = string.find(self.text, "{", wordIndex)
		local block = ""
		if bracesIndex ~= nil then
			block = string.sub(self.text, wordIndex, bracesIndex - 1)
		else
			block = string.sub(self.text, wordIndex, #self.text)
		end
		table.insert(blocks, block)
	end

	local drawX = 0
	local drawY = 0
	local charCounter = 0

	-- iterate through "style blocks"
	for i, v in ipairs(blocks) do
		textStyler:setStyle(styles[i])
		textStyler:drawStyle()
		self.textRender:setFont(love.graphics.getFont())

		-- iterate through words
	    for word in string.gmatch(v, "%S+") do

	        -- calculate word width
	        self.textRender:add(word)
	        local addWidth = self.textRender:getWidth()
	        lineWidth = drawX + addWidth

	        -- check if word extends beyond bounds
	        if (lineWidth > self.rect.width) then
	            drawY = drawY + love.graphics.getFont():getHeight()
	            drawX = 0
	        end

	        -- iterate through characters
	        for char in string.gmatch(word, ".") do
	        	self.textRender:set(char)

	        	-- draw character
	        	love.graphics.draw(self.textRender, 
	        		drawX + math.sin(love.timer.getTime() * self.wiggleSpeed + charCounter * self.wiggleOffset) * self.wiggleStrength, 
	        		drawY + math.cos(love.timer.getTime() * self.wiggleSpeed + charCounter * self.wiggleOffset) * self.wiggleStrength)
	        	drawX = drawX + self.textRender:getWidth()
	        	charCounter = charCounter + 1
	        end

	        -- draw spacing
	        self.textRender:set(" ")
	        love.graphics.draw(self.textRender, drawX, drawY)
	        drawX = drawX + self.textRender:getWidth()
	    end 
	end

	love.graphics.pop()
end