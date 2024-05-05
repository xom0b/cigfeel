TextRect = Object:extend()

function TextRect:new(rect)
	self.rect = rect
	self.text = ""
	self.textRender = love.graphics.newText(love.graphics.getFont(), "")
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

function TextRect:update(dt)
end

function TextRect:parseStyle(word)
end

function TextRect:draw()
	self.rect:draw()

	love.graphics.push()
	love.graphics.applyTransform(self.rect.transform)
	love.graphics.setColor(1, 1, 1, 1)

	local offsetLineHeight = 20
	local xOffset = 0
	local yOffset = 0
	for style in string.gmatch(self.text, "%b{}") do
		--print(style)
	end
	
	local style = ""
	local readingStyle = false

	local letterCount = 0

	local styles = {}
	for style in string.gmatch(self.text, "%b{}") do
		style = string.gsub(style, '%W', '')
		table.insert(styles, style)
		print(style)
	end

	local blocks = {}
	for wordIndex in string.gmatch(self.text, "%b{}()") do
		local bracesIndex = style.find(self.text, "{", wordIndex)
		local block = ""
		if bracesIndex ~= nil then
			block = string.sub(self.text, wordIndex, bracesIndex - 1)
		else
			block = string.sub(self.text, wordIndex, #self.text)
		end
		table.insert(blocks, block)
		print(block)
	end

	local yOffset = 0
	for i, v in ipairs(blocks) do
		textStyler:setStyle(styles[i])
		textStyler:drawStyle()
		self.textRender:setFont(love.graphics.getFont())
		self.textRender:setf(blocks[i], self.rect.width, "center")
		love.graphics.draw(self.textRender, 0, yOffset)
		yOffset = yOffset + self.textRender:getHeight()
	end

--[[
	for c in string.gmatch(self.text, ".") do
		if c == "{" then
			readingStyle = true;
		else
			if readingStyle then
				if c == "}" then
					textStyler:setStyle(style)
					textStyler:drawStyle()
					style = ""
					readingStyle = false
				else
					style = style..c
				end
			else
				if (string.gmatch(c, "%s+")) then
					self.textRender:set(c)
				else
					self.textRender:setf(c, self.rect.width, "left")
				end
				self.textRender:setFont(love.graphics.getFont())

				local newOffset = xOffset + self.textRender:getWidth()
				
				if (newOffset > self.rect.width) then
					xOffset = 0
					yOffset = yOffset + offsetLineHeight
				end
				letterCount = letterCount + 1
				--love.graphics.draw(self.textRender, xOffset, yOffset + math.sin(love.timer.getTime() * math.pi + letterCount) * 2);
				
				love.graphics.draw(self.textRender, xOffset, yOffset);

				xOffset = xOffset + self.textRender:getWidth()
			end
		end
	end
]]
	love.graphics.pop()
end