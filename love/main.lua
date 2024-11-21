function love.load(args, unfilteredArgs)
    require "loader"
    loader.loadClasses()

    textHistory = TextRect(Rectangle(150, 0, 500, 500), "bottomleft", 28)
    textHistory:setText("{default}this is some default text.{bold}more text, bold this time.{italic}finally, italic styles.{boldItalic}styled, but bold and italics.{default}this is some text that overflows to the next line, on and on and on we have text.")
    --t:setText("{default}does this break {italic, something} this is italic {this could be fuck all} and now we're here at the end")

    textInput = TextRect(Rectangle(150, 500, 500, 100), "topleft", 28)
    textInput:setText("{default}this is where you'll input text")
end

function love.textinput(text)
    textHistory:appendText(text)
    textInput:appendText(text)
end

function love.keypressed(key)
    textHistory:keypressed(key)
    textInput:keypressed(dt)
end

function love.update(dt)
    textHistory:update(dt)
    textInput:update(dt)
end

function love.draw()
    textHistory:draw()
    textInput:draw()
end