DefaultController = Object:extend()

function DefaultController:new()
	local padding_w = 200
    local padding_b = 150

	self.textHistory = TextRect(Rectangle(padding_w, -- x position
                                     	  0, 
                                     	  love.graphics.getWidth() - padding_w * 2, 
                                     	  love.graphics.getHeight() - padding_b), "bottomleft", 28)

    --self.textHistory:setText("{default}this \nis some default\ntext.{bold}more text, bold this time.{italic}finally, italic styles.{boldItalic}styled, but bold and italics.{default}this is some text that overflows to the next line, on and on and on we have text.")

    self.textInput = TextRect(Rectangle(padding_w, 
                                   		love.graphics.getHeight() - padding_b, 
                                   		love.graphics.getWidth() - padding_w * 2, 
                                   		padding_b), "topleft", 28)

    --self.textInput:setText("{default}this is where you'll input text")
end

function DefaultController:textinput(text)
	self.textInput:appendText(text)
end

function DefaultController:keypressed(key)
	if key == "backspace" then
		self.textInput:removeText()
	elseif key == "return" then
		self.textHistory:prependNewLine()
		self.textHistory:prependText(self.textInput:getText())
		self.textInput:setText("")
	end
end

function DefaultController:draw()
	self.textInput:draw()
	self.textHistory:draw()
end