from pyFunctions import get_labyrinth

def test_get_labyrinth():
    '''
    Funcion que testea get_labyrinth
    '''
    dim, lab, start, obj = get_labyrinth("./test_files/test_labyrinth1.txt")
    assert dim == 2
    assert lab == [['I','0'],['0','X']]
    assert start == (0,0)
    assert obj == (1,1)
    
    dim, lab, start, obj = get_labyrinth("./test_files/test_labyrinth2.txt")
    assert dim == 4
    assert lab == [['0','0','1','X'], ['1','0','0','0'], ['0','1','1','0'], ['I','0','0','1']]
    assert start == (3,0)
    assert obj == (0,3)
    
    
from pyFunctions import solve_labyrinth

def test_solve_labyrinth():
    '''
    Funcion que testea solve_labyrinth
    '''
    result = {
        (0,0): None,
        (1,0): (0,0),
        (0,1): (0,0),
        (1,1): (1,0)
    }
    
    assert solve_labyrinth([['I','0'],['0','X']], 2, (0,0)) == result
    assert solve_labyrinth([['0','0','1','X'], ['1','0','0','0'], ['0','1','1','0'], ['I','0','0','1']], 4, (3,0)) == None