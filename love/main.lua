function love.load(args, unfilteredArgs)
    require "loader"
    loader.loadClasses()

    local prefixText1 = "prefix_test"
    if containsPrefix(prefixText1, "prefix") then print("TEST 1 SUCCESS") else print("TEST 1 FAILED") end
    if not containsPrefix(prefixText1, "preas") then print("TEST 2 SUCCESS") else print("TEST 2 FAILED") end
    if containsSuffix(prefixText1, "test") then print("TEST 3 SUCCESS") else print("TEST 3 FAILED") end
    if not containsSuffix(prefixText1, "testes") then print("TEST 4 SUCCESS") else print("TEST 4 FAILED") end


    defaultController = DefaultController()
end

function love.textinput(text)
    defaultController:textinput(text)
end

function love.keypressed(key)
    defaultController:keypressed(key)
end

function love.update(dt)
end

function love.draw()
    defaultController:draw()
end