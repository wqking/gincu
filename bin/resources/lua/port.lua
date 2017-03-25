port = {}
port.GPoint = gincu.GVector2
port.GSize = gincu.GSize
port.createPoint = function(x, y)  local p = port.GPoint(); p.x = x; p.y = y; return p; end
port.createScale = function(x, y)  local p = port.GPoint(); p.x = x; p.y = y; return p; end
port.createSize = function(w, h)  local p = port.GSize(); p.width = w; p.height = h; return p; end

