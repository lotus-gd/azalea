import gd, itertools
from cube import calculate_cube
from ball import calculate_ball
from helpers import average

client = gd.Client()

def calculate_ship(editor: gd.api.Editor, level: gd.Level, portal: gd.api.Object, speed, portal_count: int):
    pass

def calculate_ufo(editor: gd.api.Editor, level: gd.Level, portal: gd.api.Object, speed, portal_count: int):
    pass

def calculate_wave(editor: gd.api.Editor, level: gd.Level, portal: gd.api.Object, speed, portal_count: int):
    pass

def calculate_robot(editor: gd.api.Editor, level: gd.Level, portal: gd.api.Object, speed, portal_count: int):
    pass

def calculate_spider(editor: gd.api.Editor, level: gd.Level, portal: gd.api.Object, speed, portal_count: int):
    pass

modes = {gd.PortalType.CUBE: calculate_cube,
        gd.PortalType.SHIP: calculate_ship,
        gd.PortalType.BALL: calculate_ball,
        gd.PortalType.BALL: calculate_ufo,
        gd.PortalType.UFO: calculate_ufo,
        gd.PortalType.WAVE: calculate_wave,
        gd.PortalType.ROBOT: calculate_robot,
        gd.PortalType.SPIDER: calculate_spider,
        gd.Gamemode.CUBE: calculate_cube,
        gd.Gamemode.SHIP: calculate_ship,
        gd.Gamemode.BALL: calculate_ball,
        gd.Gamemode.BALL: calculate_ufo,
        gd.Gamemode.UFO: calculate_ufo,
        gd.Gamemode.WAVE: calculate_wave,
        gd.Gamemode.ROBOT: calculate_robot,
        gd.Gamemode.SPIDER: calculate_spider}

def main():
    totalstar = []
    database = gd.api.save.load()
    levels = database.load_my_levels()
    #level = levels.get_by_name("star test")
    level = client.run(client.get_level(34281293)) # id
    editor = level.open_editor()

    startspeed = editor.get_start_speed()
    mode = modes.get(editor.header.gamemode)
    star = mode(editor, level, gd.api.Object(x=0), startspeed, -1)
    totalstar.append(star)
    
    portal_count = 0
    for portal, speed in itertools.zip_longest(editor.get_portals(), editor.get_speeds()):
        try:
            speed = gd.Speed.from_name(gd.SpeedChange(speed.id).name)
        except AttributeError: # fix speed later
            pass
        if portal.id == 10 or portal.id == 11 or portal.id == 45 or portal.id == 46 or portal.id == 101 or portal.id == 99 or portal.id == 286 or portal.id == 287 or portal.id == 747 or portal.id == 749:
            # speed portals and other extra portals
            continue
        mode = modes.get(gd.PortalType(portal.id))
        if mode:
            star = mode(editor, level, portal, speed, portal_count)
            if star is not None:
                totalstar.append(star)
        portal_count += 1
    i = 0
    for star in totalstar:
        totalstar[i] = round(star, 2)
        i += 1
    print(totalstar)
    return round(average(totalstar), 2)
        
if __name__ == "__main__":
    star = main()
    print(star)