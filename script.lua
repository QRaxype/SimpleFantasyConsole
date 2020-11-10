--Comment
t = 0
T = 120
dx = 0
dy = 0

sp={4,0,0,4,
	0,0,0,0,
	2,0,0,2,
	0,2,2,0}


function draw3pix(ox, oy, c)
	for i = -1, 1 do
		for j = -1, 1 do
			pix(ox+i, oy+j, c)
		end
	end
end

function _spr(vspr,x,y,size,trans)
	trans = trans or -1
	for i=0, size-1 do
		for j=0, size-1 do
			if vspr[j*size+i+1] ~= trans then
				pix(x+i, y+j, vspr[j*size+i+1] or 0)
			end
		end
	end
end

function Init()
	cls(0)
	--pal(2, 0x000000FF)
end
function Tick(dt)
	cls(0);
	if t%(T/30) ==0 then
		if key(71) then dx=dx-1 end
		if key(72) then dx=dx+1 end
		if key(73) then dy=dy-1 end
		if key(74) then dy=dy+1 end
	end
	
	_spr(sp, 32, 32, 4, 0)
	
	draw3pix(dx, dy, 1);
	--pix(x, y, 2)
	if t%(T/2) == 0 then
		--pal(2, pal(2)+0x000100)
	end
end
