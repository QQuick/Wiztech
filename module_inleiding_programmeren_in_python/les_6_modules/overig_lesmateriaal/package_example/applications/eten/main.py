# Standard modules
import sys as ss
import os

# Third party modules
pass

# Expand search path with proprietary packages directory
ss.path.append (
    f'{os.path.dirname (os.path.abspath (__file__))}/../../proprietary_packages'
)

# Proprietary modules
import toetje as tt
import toetje.aardbijen as ab
import toetje.slagroom as sr

# Private modules
import koffie as kf

# Definition of classes and functions
def show ():
    print ('\nWaar heb ik nu eens trek in?')
    input ()

# Main line
show ()
tt.show ()
ab.show ()
sr.show ()
kf.show ()
