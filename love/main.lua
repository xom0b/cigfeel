function love.load(args, unfilteredArgs)
    require "loader"
    loader.loadClasses()

    t = TextRect(Rectangle(100, 100, 500, 500))
    t:setText("{default}this is some default text.{bold}more text, bold this time.{italic}finally, italic styles.{boldItalic}styled, but bold and italics.{default}this is some text that overflows to the next line, on and on and on we have text.")
    --t:setText("{default}does this break {italic, something} this is italic {this could be fuck all} and now we're here at the end")

end


function love.textinput(text)
    t:appendText(text)
end

function love.keypressed(key)
    t:keypressed(key)
end

function love.update(dt)
    t:update(dt)
end

function love.draw()
    t:draw()
end