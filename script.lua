--Comment
t = 0
T = 120

function Init()
	print("FantasyConsole is Work?!");
	cls(1)
	--pix(239, 135, 0)
end

function Tick(dt)
	if t%(T/4) ==0 then
		pix(math.random(0, 240-1), math.random(0, 136-1), 0);
	end
	t=t+1
end
