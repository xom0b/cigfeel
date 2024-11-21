function ternary(condition, T, F)
	if condition then return T else return F end
end

function containsPrefix(s, prefix)
	if s == nil or prefix == nil then
		return false
	elseif string.len(s) < string.len(prefix) then 
		return 
	elseif string.sub(s, 1, string.len(prefix)) == prefix then
		return true
	else
		return false
	end
end

function containsSuffix(s, suffix)
	if s == nil or suffix == nil then
		return false
	elseif string.len(s) < string.len(suffix) then 
		return  false
	elseif string.sub(s, string.len(s) - string.len(suffix) + 1, string.len(s)) == suffix then
		return true
	else
		return false
	end
end