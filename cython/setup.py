from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
from Cython.Build import cythonize
import os

include_dir = os.path.abspath(os.path.join(os.path.pardir, 'src'))
lib_dir = os.path.abspath(os.path.join(os.path.pardir, 'src', 'build'))

exts = Extension(
    'face', ['face.pyx'], 
    include_dirs=[include_dir],
    library_dirs=[lib_dir],
    runtime_library_dirs=[lib_dir],
    libraries=["faces"],
    language="c++"
)

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = [exts]
)
