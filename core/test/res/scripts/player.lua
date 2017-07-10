local speed = 100

-- Function running once, at start of game
function init()

end


-- Function running non-stop
function update(deltaTime)
    if inputManager.isKeyPressed(KEY_RIGHT) then
        move(vec2.new(speed * deltaTime, 0))
    elseif inputManager.isKeyPressed(KEY_LEFT) then
        move(vec2.new(-speed * deltaTime, 0))
    elseif inputManager.isKeyPressed(KEY_UP) then
        move(vec2.new(0, -speed * deltaTime * 10))
    end
end