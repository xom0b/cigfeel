function love.load(args, unfilteredArgs)
    require "loader"
    loader.loadClasses()

    r1 = Rectangle(100, 100, 100, 100)
    r2 = Rectangle(300, 300, 175, 175)
    r3 = Rectangle(500, 200, 250, 250)
    r1:setColor(Color(1, 0, 0 , 1))
    r2:setColor(Color(0, 1, 0 , 1))
    r3:setColor(Color(0, 0, 1 , 1))

    t = TextRect(Rectangle(100, 100, 500, 500))
    t:setText("this is a test of some text")
end

function love.textinput(text)
    t:appendText(text)
end

function love.keypressed(key)
    if key == "backspace" then
        t:removeText()
    end

    if key == "f1" then
        textStyler:advanceStyle()
    end
end

function love.update(dt)
    r1:update(dt)
    r2:update(dt)
    r3:update(dt)
    t:update(dt)
end

function love.draw()
    r1:draw()
    r2:draw()
    r3:draw()
    t:draw()
end