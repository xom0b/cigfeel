TextRect = Object:extend()

function TextRect:new(rect)
	self.rect = rect
	self.text = ""
end

function TextRect:setText(text)
	self.text = text
end

function TextRect:appendText(text)
	self.text = self.text..text
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
	love.graphics.push()
	love.graphics.setColor(1, 1, 1, 1)
	love.graphics.applyTransform(self.rect.transform)
	textStyler:current()
	love.graphics.printf(self.text, self.rect.transform, self.rect.width, "left")
	love.graphics.pop()
end