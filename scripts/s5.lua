--Comment
t = 0
T = 120
dx = 0
dy = 0
test = 50000

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

ma = {
	n = 4, m = 4,
	data = {
		1, 1, 2, 2,
		1, 1, 1, 2,
		1, 2, 1, 2,
		1, 2, 1, 1,
	}
}

mb = {
	n = 4, m = 4,
	data = {
		1, 1, 2, 2,
		1, 1, 1, 2,
		1, 2, 1, 2,
		1, 2, 1, 1,
	}
}

function dot(v1, v2)
	local sum = 0
	for i=1, #v1 do
		sum = sum + v1[i] * v2[i]
	end
	return sum
end
function mxmul(ma, mb)
	local v1 = {};
	local v2 = {};
	if ma.n == mb.m then
		mc = {n = mb.n, m = ma.m, data = {}}
		for j=1, mc.m do
			for i=1, mc.n do
				for n=1, ma.n do
					v1[n] = ma.data[(j-1)*ma.m+n]
				end
				for m=1, mb.m do
					v2[m] = mb.data[(m-1)*mb.n+i]
				end
				mc.data[(j-1)*mc.m+(i-1)+1] = dot(v1, v2)
			end
		end
		return mc
	end
end

function print_vector(vec)
	local str = ""
	for i=1, #vec do
		str = str..vec[i]..", ";
	end
	str = string.sub(str, 1, #str-2)
	print(str)
end

function print_matrix(mx)
	for i=1, mx.m do
		print_vector(table.pack(table.unpack(mx.data, 1+(i-1)*mx.n, 4+(i-1)*mx.n)))
	end
end

function Init()
	cls(1)
	--pal(2, 0x000000FF)
end
function Tick(dt)
	cls(1);
	if t==1 then
	
	for i = 1, test do
		--pix(math.random(0, 240-1), math.random(0, 136-1), 0)
		mx = mxmul(ma, mb)
		--print("Matrix: ")
		--print_matrix(mx)
	end
	end
	if t==2 then
		print("ms: "..dt*1000)
		exit()
	end
	t=t+1
end
