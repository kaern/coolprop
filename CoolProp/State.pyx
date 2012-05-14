cdef extern from "CoolProp.h":
    double Props(char,char,double,char,double,char*)
    void UseSinglePhaseLUT(int)
    double DerivTerms(char *, double, double, char*)
    
cdef class State:
    """
    A class that contains all the code that represents a thermodynamic state
    """
    
    def __init__(self,bytes Fluid,dict StateDict,double xL=-1.0,Liquid='',bint LUT=True):
        self.Fluid=Fluid 
        self.xL=xL
        self.Liquid=Liquid
        
        #Parse the inputs provided
        self.update(StateDict)
        
        if LUT==True:
            UseSinglePhaseLUT(1)
        else:
            UseSinglePhaseLUT(0)
            
    def __reduce__(self):
        d={}
        d['xL']=self.xL
        d['Liquid']=self.Liquid
        d['Fluid']=self.Fluid
        d['T']=self.T_
        d['rho']=self.rho_
        return rebuildState,(d,)
          
    cpdef update(self,dict params, double xL=-1.0):
        """
        *params* is a list(or tuple) of strings that represent the parameters 
        that have been updated and will be used to fix the rest of the state. 
        ['T','P'] for temperature and pressure for instance
        """
        
        # If no value for xL is provided, it will have a value of -1 which is 
        # impossible, so don't update xL
        if xL>0:
            #There is liquid
            self.xL=xL
            self.hasLiquid=True
        else:
            #There's no liquid
            self.xL=0.0
            self.hasLiquid=False
        
        #You passed in a dictionary, use the values to update the state
        if 'T' not in params:
            raise AttributeError
            
        #Consume the 'T' key since it is required (TODO?)
        self.T_=float(params.pop('T'))
            
        #Given temperature and pressure, determine density of gas 
        # (or gas and oil if xL is provided)
        if abs(self.xL)<=1e-15:
            #Get the density if T,P provided, or pressure if T,rho provided
            if 'P' in params:
                self.p_=params['P']
                self.rho_=Props('D','T',self.T_,'P',self.p_,self.Fluid)
            elif 'D' in params:
                self.rho_=params['D']
                self.p_=Props('P','T',self.T_,'D',self.rho_,self.Fluid)
            
        elif self.xL>0 and self.xL<=1:
            raise ValueError('Need more code here')
        else:
            raise ValueError('xL must be between 0 and 1')
        
    property rho:
        def __get__(self):
            return self.rho_
            
    property p:
        def __get__(self):
            return self.p_
            
    property T:
        def __get__(self):
            return self.T_
    
    property h:
        def __get__(self):
            return Props('H','T',self.T_,'D',self.rho_,self.Fluid)
            
    property u:
        def __get__(self):
            return Props('U','T',self.T_,'D',self.rho_,self.Fluid)
            
    property s:
        def __get__(self):
            return Props('S','T',self.T_,'D',self.rho_,self.Fluid)
    
    property cp:
        def __get__(self):
            return Props('C','T',self.T_,'D',self.rho_,self.Fluid)
            
    property cv:
        def __get__(self):
            return Props('O','T',self.T_,'D',self.rho_,self.Fluid)
            
    property visc:
        def __get__(self):
            return Props('V','T',self.T_,'D',self.rho_,self.Fluid)
            
    property k:
        def __get__(self):
            return Props('L','T',self.T_,'D',self.rho_,self.Fluid)
            
    property Prandtl:
        def __get__(self):
            return self.cp * self.visc / self.k
            
    property dpdT:
        def __get__(self):
            return DerivTerms('dpdT',self.T_,self.rho_,self.Fluid)
    
    cpdef speed_test(self,int N):
        from time import clock
        cdef int i
        cdef char * k
        cdef char * Fluid = self.Fluid
        print 'Direct c++ call to CoolProp without the Python call layer'
        keys = ['H','P','S','U','C','O']
        for key in keys:
            t1=clock()
            k=key
            for i in range(N):
                Props(k[0],'T',self.T,'D',self.rho,Fluid)
            t2=clock()
            print 'Elapsed time for {0:d} calls for "{1:s}" at {2:g} us/call'.format(N,key,(t2-t1)/N*1e6)
    
    def __str__(self):
        units={'T': 'K', 
               'p': 'kPa', 
               'rho': 'kg/m^3',
               'h':'kJ/kg',
               'u':'kJ/kg',
               's':'kJ/kg/K',
               'visc':'Pa-s',
               'k':'kW/m/K',
               'cp':'kJ/kg/K',
               'cv':'kJ/kg/K'}
        s=''
        for k,v in self.__dict__.iteritems():
            if k in units:
                s+=k+' = '+str(v)+' '+units[k]+'\n'
            else:
                s+=k+' = '+str(v)+' NO UNITS'+'\n'
        return s
        
    cpdef copy(self):
        ST=State(self.Fluid,{'T':self.T,'D':self.rho})
        return ST
    
def rebuildState(d):
    S=State()
    S.xL = d['xL']
    S.Liquid=d['Liquid']
    S.Fluid=d['Fluid']
    S.update({'T':d['T'],'D':d['rho']})
    return S