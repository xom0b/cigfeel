TextRect = Object:extend()

function TextRect:new(rect)
	self.rect = rect
	self.text = ""
	self.textRender = love.graphics.newText(love.graphics.getFont(), "")
	self.lines = {}
end

function TextRect:setText(text)
	self.text = text
	self:rebuild()
end

function TextRect:appendText(text)
	self.text = self.text..text
	self:rebuild()
end

function TextRect:appendNewLine()
	self.text = self.text.."\n"
end

function TextRect:rebuild()
	self:getStyleBoxes()

	local lineIndex = 1
	local lineWidth = 0

	local lines = {} -- clear 
	table.insert(lines, { width = 0, words = {}})


	for word in string.gmatch(self.text, "%S+") do

		-- calculate word width
		self.textRender:add(word)
		local addWidth = self.textRender:getWidth()
		lineWidth = lineWidth + addWidth

		-- check if word extends beyond bounds
		if (lineWidth > self.rect.width) then
			lineIndex = lineIndex + 1
			lineWidth = addWidth
			table.insert(lines, { width = addWidth, words = { word }})
		else
			-- add word to line
			table.insert(lines[lineIndex].words, word)
			lines[lineIndex].width = lineWidth
		end
	end

	for i, v in ipairs(lines) do
		print(string.format("index: %i | width: %i", i, v.width))
		for j, b in ipairs(v.words) do
			--print(string.format("word: %s", b))
		end
	end
end

function TextRect:getStyleBoxes()
	
	local boxes = {}
	local boxIndex = 1
	local stringIndex = 1

	while stringIndex < self.text:len() do
		local openIndex = self.text:find("{", stringIndex)
		if openIndex then
			if openIndex > 1 then
				-- found string
				local currentString = self.text:sub(stringIndex, openIndex - 1)
				boxes[boxIndex].string = currentString
				boxIndex = boxIndex + 1
			end
			local closeIndex = self.text:find("}", openIndex)
			if closeIndex then
				-- found style
				local currentStyle = self.text:sub(openIndex, closeIndex)
				table.insert(boxes, {style = currentStyle, string = ""})
				stringIndex = closeIndex + 1
			else
				print("Error. Uneven style boxes").
				stringIndex = self.text:len()
			end
		else
			-- final word
			if stringIndex < self.text:len() then
				local currentString = self.text:sub(stringIndex, self.text:len())
				boxes[boxIndex].string = currentString
			end
			stringIndex = self.text:len()
		end
	end

	for i, box in ipairs(boxes) do
		print("style: "..box.style.." | string: "..box.string)
	end
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
	end

	local yOffset = 0
	local xOffset = 0
	for i, v in ipairs(blocks) do
		textStyler:setStyle(styles[i])
		textStyler:drawStyle()
		self.textRender:setFont(love.graphics.getFont())
		self.textRender:setf(blocks[i], self.rect.width, "left")
		love.graphics.draw(self.textRender, 0, yOffset)
	end

	love.graphics.pop()
end