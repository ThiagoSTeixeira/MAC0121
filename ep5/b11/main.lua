local collision_damage = 5
local projectile_damage = 10
local empty_damage = 5
local control_point = {
	score = 5,
	bullets = 7,
	obstacles = 3
}
local max_turns = 50
local obstacle_turns = 5
local turn_time = 0.75
local turn_count = 0

game_playing = true

function love.keypressed(key, scancode, isrepeat)
	if key == "1" then turn_time = 0.75 end
	if key == "2" then turn_time = 0.5 end
	if key == "3" then turn_time = 0.25 end
	if key == "4" then turn_time = 0.125 end
	if key == "5" then turn_time = 0 end
	if key == "0" then turn_time = 10000 end
end

function love.load()
	math.randomseed(os.time())
	math.random() math.random()
	m = 12
	n = 10
	grid = {m = m, n = n}
	temp_grid = {}
	extra_info = {}
	for i = 1, m do
		grid[i] = {}
		extra_info[i] = {}
		temp_grid[i] = {}
		for j = 1, n do
			grid[i][j] = {0}
			-- 1 - control point, 2 - explosion
			extra_info[i][j] = {math.random() < .075, false}
			temp_grid[i][j] = {0}
		end
	end

	tile0 = love.graphics.newImage "resources/tile.png"
	tile_control = love.graphics.newImage "resources/control.png"
	tile1 = love.graphics.newImage "resources/obstacle.png"
	tile3 = love.graphics.newImage "resources/projectile.png"
	tile_expl = love.graphics.newImage "resources/explosion.png"
	love.window.setTitle "Robots!"

	local player_imgs = {}
	local colors = {{0, 255, 0}, {80, 80, 250}, {255, 0, 0}, {170, 0, 220}}
	for i = 1, 4 do
		player_imgs[i] = love.graphics.newImage(string.format("resources/player%d.png", i))
	end
	for i = 2, 4 do -- shuffle
		local i_ = math.random(i)
		player_imgs[i], player_imgs[i_] = player_imgs[i_], player_imgs[i]
		colors[i], colors[i_] = colors[i_], colors[i]
	end

	players = {}

	local pn = 1
	local ex = love.filesystem.exists
	while ex("robot_ai" .. pn .. ".so") do
		players[pn] = {
			hp = 100,
			bullets = 25,
			obstacles = 10,
			score = 0,
			dir = math.random(6) - 1,
			song_played = -3,
			index = pn
		}
		players[pn].ai = require("robot_ai" .. pn)
		players[pn].img = player_imgs[pn]
		players[pn].color = colors[pn]
		local pos
		repeat
			pos = {math.random(m), math.random(n)}
		until grid[pos[1]][pos[2]][1] == 0
		grid[pos[1]][pos[2]] = {2, players[pn]}
		pn = pn + 1
	end

	for i = 1, m do
		for j = 1, n do
			if grid[i][j][1] == 2 then
				local name = grid[i][j][2].ai.prepare_game(grid, {i, j}, extra_info, max_turns)
				grid[i][j][2].name = name or string.format("Player %d", grid[i][j][2].index)
			end
		end
	end

	sound = {}

end

do
	local neighbors = {
		{{-1, 0}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}},
		{{-1, 0}, {-1, -1}, {0, -1}, {1, 0}, {0, 1}, {-1, 1}}
	}

	function get_neighbor(i, j, dir)
		return i + neighbors[(j % 2) + 1][dir + 1][1], j + neighbors[(j % 2) + 1][dir + 1][2]
	end
end

function damage(player, dam)
	player.hp = player.hp - dam
	player.score = player.score - dam
	player.damaged = true
end

function add_score(player, sco)
	player.score = player.score + sco
end

function shoot(i, j, dir)
	local ni, nj = get_neighbor(i, j, dir)
	local p = grid[i][j][2]
	if p.bullets == 0 then
		damage(p, empty_damage)
		return
	end
	p.bullets = p.bullets - 1
	if not grid[ni] or not grid[ni][nj] or grid[ni][nj][1] == 1 then return end
	local a = grid[ni][nj]
	if a[1] == 2 then
		damage(a[2], projectile_damage)
		add_score(p, projectile_damage)
	elseif a[1] == 3 then
		grid[ni][nj] = {0}
		extra_info[ni][nj][2] = true
	else
		a[1] = 3
		a[2] = {dir = dir, owner_index = p.index}
	end
end

function place_obstacle(i, j, dir)
	local ni, nj = get_neighbor(i, j, dir)
	local p = grid[i][j][2]
	if p.obstacles == 0 then
		damage(p, empty_damage)
		return
	end
	p.obstacles = p.obstacles - 1
	if not grid[ni] or not grid[ni][nj] or grid[ni][nj][1] == 1 or grid[ni][nj] == 2 then return end
	local a = temp_grid[ni][nj]
	if a[1] == 1 then
		if not a.multiple then
			a.multiple = true
			a.owners = {a[2].owner_index}
			a[2] = nil
		end
		table.insert(a.owners, p.index)
	else
		a[1] = 1
		a[2] = {turns_left = obstacle_turns, owner_index = p.index}
	end
end

function process_obstacles()
	for i = 1, m do
		for j = 1, n do
			if temp_grid[i][j][1] == 1 then
				local a = temp_grid[i][j]
				if a.multiple then
					for _, owner in ipairs(a.owners) do
						damage(players[owner], collision_damage)
					end
				else
					grid[i][j] = a
				end
			end
		end
	end
end

local actions = {
	-- faz nada (ou controla control point)
	[0] = function(i, j)
		if extra_info[i][j][1] then
			local p = grid[i][j][2]
			for att, value in pairs(control_point) do
				p[att] = p[att] + value
			end
		end
	end,
	-- coloca obstaculo na esquerda-tras
	[10] = function(i, j)
		place_obstacle(i, j, (4 + grid[i][j][2].dir) % 6)
	end,
	-- coloca obstaculo atras
	[11] = function(i, j)
		place_obstacle(i, j, (3 + grid[i][j][2].dir) % 6)
	end,
	-- coloca obstaculo na direita-tras
	[12] = function(i, j)
		place_obstacle(i, j, (2 + grid[i][j][2].dir) % 6)
	end,
	-- gira para a esquerda
	[30] = function(i, j)
		grid[i][j][2].dir = (5 + grid[i][j][2].dir) % 6
	end,
	-- gira para a direita
	[31] = function(i, j)
		grid[i][j][2].dir = (1 + grid[i][j][2].dir) % 6
	end,
	-- atira para a esquerda-frente
	[40] = function(i, j)
		shoot(i, j, (5 + grid[i][j][2].dir) % 6)
	end,
	-- atira para frente
	[41] = function(i, j)
		shoot(i, j, grid[i][j][2].dir)
	end,
	-- atira para direita-frente
	[42] = function(i, j)
		shoot(i, j, (1 + grid[i][j][2].dir) % 6)
	end
}

function eliminate_wrong(walk)
	for player, pos in pairs(walk) do
		local x, y = pos[1], pos[2]
		local nx, ny = get_neighbor(x, y, player.dir)
		if not grid[nx] or not grid[nx][ny] or grid[nx][ny][1] == 1 or (grid[nx][ny][1] == 2 and not grid[nx][ny][2].wannaWalk) then
			damage(player, collision_damage)
			walk[player] = nil
			if grid[nx] and grid[nx][ny] and grid[nx][ny][1] == 1 then
				add_score(players[grid[nx][ny][2].owner_index], collision_damage)
			end
		end
	end
end

function check_robot_collision(walk)
	local any_at_all = false
	local erase = {}
	for player, pos in pairs(walk) do
		local x, y = pos[1], pos[2]
		local nx, ny = get_neighbor(x, y, player.dir)
		local any = false
		for p2, pos2 in pairs(walk) do
			if p2 ~= player then
				local x2, y2 = pos2[1], pos2[2]
				local nx2, ny2 = get_neighbor(x2, y2, p2.dir)
				if (nx2 == nx and ny2 == ny) or 
				(nx2 == x and ny2 == y and ((6 - player.dir + p2.dir) % 6) == 3) --[[opposite dirs]] then
					any = true
					any_at_all = true
					damage(p2, collision_damage)
					p2.wannaWalk = false
					erase[p2] = true
				end
			end
		end
		if any then
			player.wannaWalk = false
			erase[player] = true
			damage(grid[x][y][2], collision_damage)
		end
	end

	for p in pairs(erase) do
		walk[p] = nil
	end

	return any_at_all
end

function check_projetiles()
	for i = 1, m do
		for j = 1, n do
			if grid[i][j][1] == 3 and grid[i][j][2].dir > 2 then
				local ni, nj = get_neighbor(i, j, grid[i][j][2].dir)
				if grid[ni] and grid[ni][nj] and grid[ni][nj][1] == 3 and
					((6 - grid[i][j][2].dir + grid[ni][nj][2].dir) % 6) == 3 then
					grid[i][j] = {0}
					grid[ni][nj] = {0}
					extra_info[i][j][2] = true
					extra_info[ni][nj][2] = true
				end
			end
		end
	end
end

function do_movement(walk)
	for i = 1, m do
		for j = 1, n do
			temp_grid[i][j] = {0}
		end
	end
	check_projetiles()
	--[[
		0 nothing
		1 WRONG
		3 projectile
	]]
	for p, pos in pairs(walk) do
		local x, y = pos[1], pos[2]
		local nx, ny = get_neighbor(x, y, p.dir)
		temp_grid[nx][ny] = grid[x][y]
		grid[x][y] = {0}
	end

	for i = 1, m do
		for j = 1, n do
			if grid[i][j][1] == 3 then
				local ni, nj = get_neighbor(i, j, grid[i][j][2].dir)
				if temp_grid[ni] and temp_grid[ni][nj] then
					if temp_grid[ni][nj][1] == 1 then
						table.insert(temp_grid[ni][nj][2], grid[i][j][2].owner_index)
					elseif temp_grid[ni][nj][1] == 3 then
						temp_grid[ni][nj][1] = 1
						temp_grid[ni][nj][2] = {temp_grid[ni][nj][2].owner_index, grid[i][j][2].owner_index}
					elseif temp_grid[ni][nj][1] == 2 then
						damage(temp_grid[ni][nj][2], projectile_damage)
						add_score(players[grid[i][j][2].owner_index], projectile_damage)
					else
						temp_grid[ni][nj] = grid[i][j]
					end
				end
				grid[i][j] = {0}
			end
		end
	end

	for i = 1, m do
		for j = 1, n do
			if temp_grid[i][j][1] == 2 then
				grid[i][j] = temp_grid[i][j]
			elseif temp_grid[i][j][1] == 3 then
				if grid[i][j][1] == 0 then
					grid[i][j] = temp_grid[i][j]
				elseif grid[i][j][1] == 2 then
					damage(grid[i][j][2], projectile_damage)
					add_score(players[temp_grid[i][j][2].owner_index], projectile_damage)
				end
			elseif temp_grid[i][j][1] == 1 then
				extra_info[i][j][2] = true
				if grid[i][j][1] == 2 then
					for _, ind in ipairs(temp_grid[i][j][2]) do
						damage(grid[i][j][2], projectile_damage)
						add_score(players[ind], projectile_damage)
					end
				end
			end
		end
	end
end

function turn_update()
	-- block timers
	for i = 1, m do
		for j = 1, n do
			extra_info[i][j][2] = false
			if grid[i][j][1] == 1 then
				grid[i][j][2].turns_left = grid[i][j][2].turns_left - 1
				if grid[i][j][2].turns_left == 0 then
					grid[i][j] = {0}
				end
			end
		end
	end
	for _, p in pairs(players) do
		p.damaged = false
	end
end

function end_game()
	if not game_playing then return end
	game_playing = false
	players_win = {}
	for i = 1, #players do
		players_win[i] = players[i]
	end
	table.sort(players_win, function(p1, p2) return p1.score > p2.score end)
	print(players_win[1].name)
	love.event.quit()
end

function end_turn()
	local n_players = 0
	for i = 1, m do
		for j = 1, n do
			if grid[i][j][1] == 2 then
				local p = grid[i][j][2]
				if p.hp <= 0 then
					print(p.name .. ' died')
					-- process death
					add_score(p, -250)
					grid[i][j] = {0}
					extra_info[i][j][2] = true
				else
					n_players = n_players + 1
				end
			end
		end
	end

	if n_players <= 1 then
		end_game()
	end
end

function do_turn()
	turn_update()

	for _, p in ipairs(players) do
		p.wannaWalk = false
	end
	local act_queue = {}
	local walk = {}
	for i = 1, m do
		for j = 1, n do
			if grid[i][j][1] == 2 then
				local act, song_name = grid[i][j][2].ai.process_turn(grid, {i, j}, extra_info, max_turns - turn_count)
				if act == 20 then
					players[grid[i][j][2].index].wannaWalk = true
					walk[players[grid[i][j][2].index]] = {i, j}
				else
					act_queue[#act_queue + 1] = {act, i, j}
				end
			end
		end
	end
	table.sort(act_queue, function(a, b) return a[1] < b[1] end)

	for i = 1, m do
		for j = 1, n do
			temp_grid[i][j] = {0}
		end
	end

	-- ficar parado e colocar obstaculo
	local i = 1
	while i <= #act_queue and act_queue[i][1] < 20 do
		actions[act_queue[i][1]](act_queue[i][2], act_queue[i][3])
		i = i + 1
	end

	process_obstacles()

	-- do movements
	repeat
		eliminate_wrong(walk)
	until not check_robot_collision(walk)
	do_movement(walk)


	-- girar, atirar
	while i <= #act_queue do
		actions[act_queue[i][1]](act_queue[i][2], act_queue[i][3])
		i = i + 1
	end

	end_turn()
end

count = 0
function love.update(dt)
	if not game_playing then return end
	count = count + dt
	if count >= turn_time then
		count = count - turn_time
		turn_count = turn_count + 1
		do_turn()
		if turn_count >= max_turns then
			end_game()
		end
	end
end

local small_font = love.graphics.newFont(12)
local medium_font = love.graphics.newFont(30)
local big_font = love.graphics.newFont(70)
function draw_grid()
	local w = tile1:getWidth()
	local h = tile1:getHeight()
	for i = 1, m do
		for j = 1, n do
			local x = i * w
			local y = j * h * 3 / 4
			if j % 2 == 0 then x = x + w / 2 end

			love.graphics.draw(extra_info[i][j][1] and tile_control or tile0, x, y)
			if extra_info[i][j][2] then
				love.graphics.draw(tile_expl, x, y)
			elseif grid[i][j][1] ~= 0 then
				x = x + w / 2
				y = y + h / 2
				local r = math.pi * (((grid[i][j][2].dir or 3) + 3) % 6) / 3
				if grid[i][j][1] == 2 then -- is a player
					if grid[i][j][2].damaged then
						love.graphics.setColor(255, 150, 150)
					end
					love.graphics.draw(grid[i][j][2].img, x, y, r, 1, 1, w / 2, h / 2)
					love.graphics.setColor(255, 255, 255)
				else
					love.graphics.draw(_G['tile' .. grid[i][j][1]], x, y, r, 1, 1, w / 2, h / 2)
				end
			end
		end
	end
end

function draw_player_info()
	for i = 1, #players do
		local p = players[i]
		love.graphics.setColor(p.color)
		love.graphics.print(string.format(
			'%s:\n HP: %d/100\n Bullets: %d\n Obstacles: %d\n Score: %d',
			 p.name, p.hp, p.bullets, p.obstacles, p.score), -70 + 150 * i, 5)
	end
	love.graphics.setColor(255, 255, 255)
end

function love.draw()
	love.graphics.setColor(255, 255, 255)
	love.graphics.setFont(small_font)
	love.graphics.print('Turn ' .. turn_count, 10, 10)
	draw_player_info()
	love.graphics.setFont(medium_font)
	love.graphics.translate(0, 30)
	draw_grid()
	love.graphics.translate(0, -30)
	love.graphics.setFont(big_font)
	if not game_playing then
		love.graphics.setColor(200, 60, 60)
		if not players_win[1] or not players_win[2] then return end
		if players_win[1].score == players_win[2].score then
			love.graphics.print('It\'s a draw!', 200, 200)
		else
			love.graphics.print(players_win[1].name .. ' won!!!', 100, 200)
		end
	end
end
