TextRect = Object:extend()

function TextRect:new(rect, anchor, spacing)
	self.rect = rect
	self.text = ""
	self.textRender = love.graphics.newText(love.graphics.getFont(), "")
	self.lines = {}
	self.wiggleStrength = 5
	self.wiggleSpeed = 5
	self.wiggleDivider = 8
	self.wiggleOffset = math.pi / self.wiggleDivider
	self.anchor = ternary(anchor == null, "topleft", anchor)
	self.xdirection = ternary(string.find(self.anchor, "left") ~= nil, 1, -1) -- 1 grows right, -1 grows left
	self.ydirection = ternary(string.find(self.anchor, "top") ~= nil, 1, -1) -- 1 grows down, -1 grows up
end

function TextRect:setText(text)
	self.text = text
end

function TextRect:getText()
	return self.text
end

function TextRect:appendText(text)
	self.text = self.text..text
end

function TextRect:prependText(text)
	self.text = text..self.text
end

function TextRect:appendNewLine()
	self.text = self.text.."\n"
end

function TextRect:prependNewLine()
	self.text = "\n"..self.text
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

function TextRect:draw()
	--self.rect:draw()

	if string.len(self.text) < 1 then return end

	love.graphics.push()
	love.graphics.applyTransform(self.rect.transform)
	love.graphics.setColor(1, 1, 1, 1)

	local drawX = ternary(self.xdirection == 1, 0, self.rect.width)
	local drawY = ternary(self.ydirection == 1, 0, self.rect.height - textStyler:getHeight("default"))

	local currentStyle = "default"
	textStyler:setStyle(currentStyle)
	textStyler:drawStyle()
    self.textRender:setFont(love.graphics.getFont())

    -- break into lines
    -- break into words
    -- extract styles from words
    -- check if words extend bounds
    -- draw characters
    -- NOTE: this requires all style tags belong to the same "word"
    -- ex: "{default}default text. {bold}bold text" 
    -- incorrect ex: "{default} default text.{bold} bold text"
	for line in string.gmatch(self.text, "([^\r\n]+)") do

		local lineWidth = 0
		for word in string.gmatch(line, "%S+") do

			local sanitizedWord = ""

			charIndex = 1
			while charIndex <= string.len(word) do
				-- parse style
				currentChar = word:sub(charIndex, charIndex)
				if currentChar == '{' then 
					closedIndex = string.find(word, "}", charIndex)
					if closedIndex == nil then 
						print("couldn't parse style")
					else
						currentStyle = word:sub(charIndex + 1, closedIndex - 1)
						charIndex = closedIndex

						textStyler:setStyle(currentStyle)
						textStyler:drawStyle()
				        self.textRender:setFont(love.graphics.getFont())
					end
				else
					sanitizedWord = sanitizedWord..currentChar
				end

				charIndex = charIndex + 1
			end

			local addWidth = love.graphics.getFont():getWidth(sanitizedWord)
	        lineWidth = lineWidth + addWidth

	        if (lineWidth > self.rect.width) then
	            drawY = drawY + textStyler:getHeight("default") * self.ydirection
	            drawX = ternary(self.xdirection == 1, 0, self.rect.width)
	            lineWidth = addWidth
	        end

	        -- draw characters
	        for char in string.gmatch(sanitizedWord, "%S") do
	        	self.textRender:set(char)
	        	love.graphics.draw(self.textRender, drawX, drawY) 
	        	drawX = drawX + love.graphics.getFont():getWidth(char) * self.xdirection
	        end

	        -- advance whitespaces
	        drawX = drawX + love.graphics.getFont():getWidth(" ") * self.xdirection
	        lineWidth = lineWidth + love.graphics.getFont():getWidth(" ")

		end

		-- advance newline
        drawY = drawY + textStyler:getHeight("default") * self.ydirection
		drawX = 0
	end
	
	love.graphics.pop()
end