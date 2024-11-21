loader = {}

function loader.loadClasses()
    -- internal
    utf8 = require "utf8"
    
    -- external
    Object = require "libraries.classic"

    -- cigfeel
    require "utils"
    require "color"
    require "rectangle" -- depends on Color
    require "text_rect" -- depends on Rectangle, utils
    require "text_styler"
    require "default_controller"

    -- global instances
    textStyler = TextStyler() 
end