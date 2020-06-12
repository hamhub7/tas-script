local colors = {}

function colors.rgba(r, g, b, a)
    return ((r & 0xFF) << 0) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | ((a & 0xFF) << 24)
end

function colors.rgb(r, g, b)
    return colors.rgba(r, g, b, 255);
end

return colors