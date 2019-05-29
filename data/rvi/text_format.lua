if rvi == nil then
    rvi = {}
end

rvi.set_cursive = function()
    distort(
        vector2.new(0.25, 0), 
        vector2.new(0.25, 0), 
        vector2.new(0, 0), 
        vector2.new(0, 0)
    );
end