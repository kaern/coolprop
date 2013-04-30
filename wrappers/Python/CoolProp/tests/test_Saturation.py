import CoolProp
from CoolProp.CoolProp import Props
from math import log10
import random
import numpy as np

def test_p():
    for Fluid in CoolProp.__fluids__:
        prange = (Props(Fluid,'ptriple')+1e-5, Props(Fluid,'pcrit'))
        for p in [random.uniform(*prange) for i in range(50)]:
            yield check_p,Fluid,p
        
def check_p(Fluid, p):
    Tmin = Props(Fluid,'Ttriple')
    Tcrit = Props(Fluid,'Tcrit')
    Tsat = Props('T', 'P', p, 'Q', 1, Fluid)
    assert Tsat >= Tmin and Tsat <= Tcrit
    
###############################################################################
###############################################################################

def test_T():
    for Fluid in CoolProp.__fluids__:
        for T in np.linspace(Props(Fluid,'Tmin')+1e-5, Props(Fluid,'Tcrit')-1e-5):
            yield check_T,Fluid,T
        
def check_T(Fluid, T):
    pmin = Props(Fluid,'ptriple')
    pmax = Props('P','T',Props(Fluid,'Tcrit'),'D',Props(Fluid,'rhocrit'),Fluid)
    psat = Props('P', 'T', T, 'Q', 1, Fluid)
    
if __name__=='__main__':
    import nose
    nose.runmodule()