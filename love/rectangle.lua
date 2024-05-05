Rectangle = Object:extend()

function Rectangle:new(x, y, width, height)
	self.transform = love.math.newTransform(x, y)
	self.width = width
	self.height = height
	self.Color = Color(1, 1, 1, 1)
	self.rotation = 0
end

function Rectangle:setColor(color)
	self.Color = color
end

function Rectangle:update(dt)
	self.rotation = self.rotation + dt
end

function Rectangle:draw()
	love.graphics.push()
	love.graphics.setColor(self.Color.r, self.Color.g, self.Color.b, self.Color.a)
	love.graphics.applyTransform(self.transform)
	love.graphics.rotate(self.rotation)
	love.graphics.rectangle("line", 0, 0, self.width, self.height)
	love.graphics.pop()
end