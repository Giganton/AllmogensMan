from PIL import Image
import numpy
import json

def openImage(fileName) :
    image = Image.open(fileName, 'r')
    width, height = image.size
    pixel_values = list(image.getdata())
    channels = 0;
    if image.mode == "RGB":
        channels = 3
    elif image.mode == "L":
        channels = 1
    elif image.mode == "RGBA":
        channels = 4
    return numpy.array(pixel_values).reshape((width,height,channels))

def countRiverNeighbours(pixel_values, x, y, width, height) :
    river_neighbours = 0
    if (y + 1 < height and pixel_values[y + 1][x][2] == 255) :
        river_neighbours = river_neighbours + 1
    if (y > 0 and pixel_values[y - 1][x][2] == 255) :
        river_neighbours = river_neighbours + 1
    if (x + 1 < width and pixel_values[y][x + 1][2] == 255) :
        river_neighbours = river_neighbours + 1
    if (x > 0 and pixel_values[y][x - 1][2] == 255) :
        river_neighbours = river_neighbours + 1

    return river_neighbours

def getRiverNeighbours(pixel_values, pos, width, height):
    neighbours = []
    if (pos[1] + 1 < height and pixel_values[pos[1] + 1][pos[0]][2] == 255) :
        neighbours.append((pos[0], pos[1]+1))
    if (pos[1] > 0 and pixel_values[pos[1] - 1][pos[0]][2] == 255) :
        neighbours.append((pos[0],pos[1]-1))
    if (pos[0] + 1 < width and pixel_values[pos[1]][pos[0] + 1][2] == 255) :
        neighbours.append((pos[0]+1,pos[1]))
    if (pos[0] > 0 and pixel_values[pos[1]][pos[0] - 1][2] == 255) :
        neighbours.append((pos[0]-1, pos[1]))
    return neighbours

def buildRiver(pixel_values, riverList, pos, upstream_pos, width, height):
    riverList.append(pos)
    if (countRiverNeighbours(pixel_values, pos[0], pos[1], width, height) != 2):
        return riverList
    else :
        newPos= findDownstreamNeighbour(pixel_values,pos[0],pos[1],upstream_pos[0], upstream_pos[1],width,height)
        return buildRiver(pixel_values, riverList, newPos, pos, width, height)
        
def findDownstreamNeighbour(pixel_values, x, y, upstream_x, upstream_y, width, height):
    if (y + 1 < height and pixel_values[y + 1][x][2] == 255 and not ((y + 1) == upstream_y and x == upstream_x)) :
        return x, y + 1
    if (y > 0 and pixel_values[y - 1][x][2] == 255 and not ((y - 1) == upstream_y and x == upstream_x)):
        return x, y - 1
    if (x + 1 < width and pixel_values[y][x + 1][2] == 255 and not (y == upstream_y and (x + 1) == upstream_x)):
        return x + 1, y
    if (x > 0 and pixel_values[y][x - 1][2] == 255 and not (y == upstream_y and (x - 1) == upstream_x)):
        return x - 1, y

def findRiverEndpoint(pixel_values, x, y, upstream_x, upstream_y, width, height) :
    blueVal = pixel_values[y][x][2]
    nbrs = countRiverNeighbours(pixel_values, x, y, width, height)
    if nbrs == 0 or nbrs > 4:
        raise Exception('konstigt antal agrannar')
    if (blueVal and nbrs != 2 ):
        return x, y
    else :
        downstream_x, downstream_y = findDownstreamNeighbour(pixel_values, x, y, upstream_x, upstream_y, width, height)
        return findRiverEndpoint(pixel_values, downstream_x, downstream_y, x, y, width, height)

    
    
pixel_values = openImage('karta.png')

grid = {}
grid['tiles'] = []
grid['player_starting_tiles'] = []
grid['enemy_starting_tiles'] = []
x = 0
y = 0
width = 0
height = 0
for row in pixel_values:
   
    for tile in row:
        if tile[1] == 255 :
            grid['tiles'].append({
                'x': x,
                'y': y,
                'terrain': 'field'
                })
        else :
            grid['tiles'].append({
                'x': x,
                'y': y,
                'terrain': 'none'
                })
        x = x + 1
    y = y + 1
    width = x
    x = 0

height = y
grid['width'] = width
grid['height'] = height

x = 0
y = 0

pixel_values = openImage('karta_startingPos.png')
for row in pixel_values:
    for tile in row:
        if tile[2] == 255 :
            grid['player_starting_tiles'].append({
                'x': x,
                'y': y,
                })
        elif tile[0] == 255 :
            grid['enemy_starting_tiles'].append({
                'x': x,
                'y': y,
                })
        elif tile[1] == 255 :
            grid['cursor_starting_tile'] = ({
                'x': x,
                'y': y,
                })
        x = x + 1
    y = y + 1
    x = 0
x = 0
y = 0


pixel_values = openImage('karta_floder.png')
endpoints = []
grid['rivers'] = []
'''hitta andpunkter till alla flodbitar'''
for row in pixel_values:
    for tile in row:
        if tile[2] == 255 :
            ep = findRiverEndpoint(pixel_values, x, y, -1, -1, width, height)
            if not ep in endpoints :
                endpoints.append(ep)
        x = x + 1
    y = y + 1
    x = 0

'''folj floderna ut till den andra kanten'''
alreadyAdded = False
for endpoint in endpoints :
    neighbours = getRiverNeighbours(pixel_values, endpoint, width, height)
    for neighbour in neighbours :
        for river in grid['rivers']:
            if (neighbour in river):
                alreadyAdded = True
                break
        if (alreadyAdded) :
            alreadyAdded = False
            break
        else :
            newRiver = []
            newRiver.append(endpoint)
            
            grid['rivers'].append(buildRiver(pixel_values, newRiver, neighbour, endpoint, width, height))
            
with open('encodedMap.json','w') as outfile:
    json.dump(grid, outfile)
