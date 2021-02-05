import typing, gd, decimal

allspikes, allblocks, allsaws, allslopes, allorbs = ([], [], [], [], [])

def get_objects_with_id(objects: list, id: list) -> typing.List[gd.api.Object]:
    final = []
    for o in objects:
        for i in id:
            if o.id == i:
                final.append(o)
    return final

def get_objects_in_x(objects: list, start, end) -> typing.List[gd.api.Object]:
    final = []
    for o in objects:
        if o.x > start and o.x < end:
            final.append(o)
    return final

def average(num):
    sum_num = 0
    for t in num:
        sum_num = sum_num + t           
    try:
        avg = sum_num / len(num)
    except ZeroDivisionError:
        avg = 0
    return avg

def get_spikes(objects):
    return get_objects_with_id(objects, [8, 39, 61, 103, 135, 144, # all spikes
    145, 177, 178, 179, 205, 216, 217, 218, 363, 364, 365, 366, 367,
    368, 392, 421, 422, 667, 989])
    
def get_orbs(objects):
    return get_objects_with_id(objects, [36, 84, 141, 1022, 1333, 1330, 1704, 1751])

def get_blocks(objects):
    return get_objects_with_id(objects, [1, 2, 3, 4, 5, 6, 7, 40, # all blocks
    62, 63, 65, 66, 68, 69, 70, 71, 74, 76, 77, 78, 81, 83, 90, 91,
    92, 95, 116, 117, 118, 121, 146, 147, 160, 161, 162, 165, 168,
    169, 170, 171, 172, 173, 174, 175, 176, 192, 194, 195, 196,
    197, 204, 206, 207, 208, 209, 210, 211, 212, 213, 215, 219,
    220, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257,
    260, 263, 264, 265, 267, 268, 269, 270, 271, 274, 369, 370,
    467, 468, 469, 470, 475, 661, 662, 663, 664, 841, 841, 842,
    843, 844, 845, 846, 847, 848, 867, 868])

def get_saws(objects):
    return get_objects_with_id(objects, [88, 89, 183, 184, 185, # all saws
    186, 187, 188, 675, 676, 677, 678, 679, 680, 740, 741, 742])

def get_slopes(objects):
    return get_objects_with_id(objects, [289, 291, 294, 295, 299, 301,
    305, 307, 309, 311, 315, 317, 321, 323, 326, 327, 331, 337, 337, 339,
    343, 345, 349, 351, 353, 355, 371, 372, 397, 398, 399, 483, 484, 492,
    493, 651, 652, 665, 666, 673, 674, 709, 710, 711, 712, 726, 727, 728,
    729, 826, 827, 828, 829, 877, 878, 876, 877, 895, 896])`