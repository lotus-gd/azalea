import gd
from helpers import get_objects_in_x, get_objects_with_id, average, get_spikes, get_orbs

def calculate_ball(editor: gd.api.Editor, level: gd.Level, portal: gd.api.Object, speed: gd.Speed, portal_count: int):
    # speed
    
    if speed:
        speed = gd.SpeedConstant.as_dict().get(speed.name.lower())
    else:
        speed = gd.SpeedConstant.as_dict().get(editor.get_start_speed().name.lower())
        
    # orbs
    
    try:
        orbs = get_objects_in_x(get_orbs(editor.get_objects()), portal.x, editor.get_portals()[portal_count+1].x)
    except IndexError: # no portals
        orbs = get_orbs(editor.get_objects())
    
    last = None
    orbspeed = []
    
    for o in orbs:
        if last:
            orbdistance = o.x - last.x
            if orbdistance < 0: # distance of orbs
                orbdistance = last.x - o.x
            orbspeed.append(orbdistance / 100)
        last = o

    avgorbspeed = average(orbspeed)
    
    # speed stars
    
    speedstars = (avgorbspeed * speed)
    
    # timing
    
    
    
    # timing stars
    
    timingstars = 0
    
    # final
    
    star = speedstars + timingstars
    return star