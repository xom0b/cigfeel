loader = {}

function loader.loadClasses()
    -- internal
    utf8 = require "utf8"
    
    -- external
    Object = require "libraries.classic"

    -- cigfeel
    require "color"
    require "rectangle" -- depends on Color
    require "text_rect" -- depends on Rectangle
    require "text_styler"
    textStyler = TextStyler()
end