function love.load(args, unfilteredArgs)
    require "loader"
    loader.loadClasses()

    t = TextRect(Rectangle(100, 100, 500, 500))
    --t:setText("{default}this is a test of some {bold}bold text this is some more textuals thatasdfasdf bleeds over {italic} this is some italics text {boldItalic} this is some bold italics text {default}and this is back to regular")
    t:setText("{default}does this break")

end


function love.textinput(text)
    t:appendText(text)
end

function love.keypressed(key)
    if key == "backspace" then
        t:removeText()
    elseif key == "return" then
        t:appendNewLine()
    end

    if key == "f1" then
        textStyler:advanceStyle()
    end
end

function love.update(dt)
    t:update(dt)
end

function love.draw()

    t:draw()
end