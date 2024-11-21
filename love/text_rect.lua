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
	-- TODO: cache styles and blocks

	--self.rect:draw()

	if string.len(self.text) < 1 then return end

	love.graphics.push()
	love.graphics.applyTransform(self.rect.transform)
	love.graphics.setColor(1, 1, 1, 1)

	-- sanitize
	-- if we detect no styling, insert default style
	-- if we detect a style, bump it to the front
	if string.sub(self.text, 1, 1) ~= '{' then
		local bracesStart = string.find(self.text, '{')
		local bracesEnd = string.find(self.text, '}')
		if bracesStart == nil then
			self.text = "{default}"..self.text -- no braces, insert them
		else
			local styleExtracted = string.sub(self.text, bracesStart, bracesEnd)
			self.text = styleExtracted..string.sub(self.text, 1, bracesStart - 1)..string.sub(self.text, bracesEnd + 1, #self.text)
		end
	end

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

	local drawX = ternary(self.xdirection == 1, 0, self.rect.width)
	local drawY = ternary(self.ydirection == 1, 0, self.rect.height - textStyler:getHeight("default"))
	local lineWidth = 0

	-- iterate through "style blocks"
	for i, v in ipairs(blocks) do
		textStyler:setStyle(styles[i])
		textStyler:drawStyle()
		self.textRender:setFont(love.graphics.getFont())

		-- iterate through words
	    for word in string.gmatch(v, "[\r]*[\n]*[%S]+[\r]*[\n]*") do --check for newlines on either side of the word
	    	
	    	local containsNewLineStart = containsPrefix(word, "\n") or containsPrefix(word, "\r")
	    	local containsNewLineEnd = containsSuffix(word, "\n") or containsSuffix(word, "\r")

	    	-- newlines at beginning of word
	    	if containsNewLineStart then
	    		drawY = drawY + textStyler:getHeight("default") * self.ydirection
	            drawX = ternary(self.xdirection == 1, 0, self.rect.width)
	    	end

	        -- wrap words
	        local addWidth = love.graphics.getFont():getWidth(word)
	        lineWidth = lineWidth + addWidth

	        if (lineWidth > self.rect.width) then
	            drawY = drawY + textStyler:getHeight("default") * self.ydirection
	            drawX = ternary(self.xdirection == 1, 0, self.rect.width)
	            lineWidth = addWidth
	        end

	        -- draw characters
	        for char in string.gmatch(word, "%S") do
	        	self.textRender:set(char)

	        	-- draw character
	        	love.graphics.draw(self.textRender, drawX, drawY) 
	        	drawX = drawX + love.graphics.getFont():getWidth(char) * self.xdirection
	        end

	        -- newlines at end of word
	        if containsNewLineEnd then
	    		drawY = drawY + textStyler:getHeight("default") * self.ydirection
	            drawX = ternary(self.xdirection == 1, 0, self.rect.width)
	    	else
	    		-- advance whitespaces
		        drawX = drawX + love.graphics.getFont():getWidth(" ") * self.xdirection
		        lineWidth = lineWidth + love.graphics.getFont():getWidth(" ")
		    end
	    end 
	end

	love.graphics.pop()
end