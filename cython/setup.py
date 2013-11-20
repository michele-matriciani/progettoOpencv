from distutils.core import setup, Extension
#from distutils.extension import Extension
from Cython.Distutils import build_ext
import os

include_dir = os.path.abspath(os.path.join(os.path.pardir, 'src'))
lib_dir = os.path.abspath(os.path.join(os.path.pardir, 'src', 'build'))

exts = Extension(
    'face', ['face.pyx'], 
    include_dirs = [include_dir,],
    library_dirs = [lib_dir,],
    libraries = ['faces',],
    depends=['cface.pxd',],
    
)

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = [exts]
)
